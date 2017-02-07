defmodule VercheckEx do
  require HTTPoison
  require Floki
  require Timex

  def fetch_content() do
    receive do # メッセージ受信。{送り手のpid, url, type, インデックス}が来たら以下を実行。
      {caller, url, type, i} ->
        #IO.puts "URL = #{url}"
        ret = HTTPoison.get!( url )

        %HTTPoison.Response{status_code: 200, body: body} = ret
        # HTML bodyを取得する
        # HTMLパーザー Flokiで処理
        # 名前、リリース日時を取得
        {_,_,n} = Floki.find(body, ".container strong a") |> List.first
        {_, d} = Floki.find(body, "time") |> Floki.attribute("datetime")
                                          |> List.first
                                          |> Timex.DateFormat.parse("{ISOz}")
        if(type == :type1) do # バージョン番号を取得
          #IO.puts "type1"
          {_,_,x} = Floki.find(body, ".tag-name span") |> List.first
        else
          {_,_,x} = Floki.find(body, ".css-truncate-target span") |> List.first
        end
        d =Timex.Date.local(d, Timex.Date.timezone("JST"))
        send caller, {:ok, {hd(n),hd(x),d,i}}
        # 送り手にメッセージを返したらこのプロセスは終了する
      end
  end

  def put_a_formatted_line(val) do # 1行出力
    {title, ver, date, _} = val
    l = title
    if String.length(title) < 8 do
      l = l <> "\t"
    end
    l = l <> "\t" <> ver
    if String.length(ver) < 8 do
      l = l <> "\t"
    end
    l = l <> "\t" <> Timex.DateFormat.format!(date, "%Y.%m.%d", :strftime)

    now = Timex.Date.now("JST")
    diff =  Timex.Date.diff( date, now, :days)
    if diff < 14 do
      l = l <> "\t<<<<< updated at " <> Integer.to_string(diff) <> " day(s) ago."
    end
    IO.puts(l)
  end

  def receiver(result_list, n) do # URL取得のプロセスからのメッセージを待ち受けする。nはURLの個数。
    if( length(result_list) < n ) do # 指定したURLのデータが全て揃うまで…
      receive do
        {:ok, res} -> # まだ手抜きでエラーケースを入れてない…
          receiver( result_list++[res], n ) # 変数result_listに結果を追加して再帰呼び出し
      end
    else # 結果が全て集まったらリストをソートして終了
      Enum.sort(result_list, fn(a,b) -> # sort by index number
        {_,_,_,i1} = a
        {_,_,_,i2} = b
        i1 < i2 end)|>Enum.each( fn(x) -> put_a_formatted_line x end)
    end
  end
end

urls = [ #{ URL, type, index}
  {"https://github.com/jquery/jquery/releases", :type1},
  {"https://github.com/angular/angular/releases", :type1},
  {"https://github.com/facebook/react/releases", :type2},
  {"https://github.com/PuerkitoBio/goquery/releases", :type1},
  {"https://github.com/revel/revel/releases", :type2},
  {"https://github.com/lhorie/mithril.js/releases", :type1},
  {"https://github.com/riot/riot/releases", :type1},
  {"https://github.com/atom/atom/releases", :type2},
  {"https://github.com/Microsoft/TypeScript/releases", :type2},
  {"https://github.com/docker/docker/releases", :type1},
  {"https://github.com/JuliaLang/julia/releases", :type2},
  {"https://github.com/Araq/Nim/releases", :type1},
  {"https://github.com/elixir-lang/elixir/releases", :type2},
  {"https://github.com/philss/floki/releases", :type1},
  {"https://github.com/takscape/elixir-array/releases", :type2},
]

# URLの数だけプロセスを立ち上げて待たせておく
fetchers = for _ <- 0..length(urls), do: spawn_link fn -> VercheckEx.fetch_content() end

Enum.each( Enum.with_index(urls),  fn(x) ->
 # プロセスにメッセージ{pid, URL, type, インデックス} を送る。メッセージを受け取ったプロセスは処理を開始する。
  {{u,t},i} = x # パターンマッチしている
  send Enum.at(fetchers,i), {self, u, t, i}
end)

result_list = []
VercheckEx.receiver(result_list, length(urls))
