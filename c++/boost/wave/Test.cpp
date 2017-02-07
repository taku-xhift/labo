

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <iterator>
#include <algorithm>
#include <boost/wave.hpp>
#include <boost/wave/preprocessing_hooks.hpp>
#include <boost/wave/cpplexer/cpp_lex_token.hpp>
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/filesystem.hpp>



// インクルードをグラフ化するフッククラス
class include_graph_hooks
	: public boost::wave::context_policies::default_preprocessing_hooks
{
private:

	// グラフのノード
	struct node_type {
		boost::filesystem::path absolute;    // 絶対パス
		boost::filesystem::path filename;    // ファイル名

	public:

		node_type(boost::filesystem::path const& absolute, boost::filesystem::path const& filename)
			: absolute(absolute)
			, filename(filename)
		{}

		friend bool operator==(node_type const& lhs, node_type const& rhs) {
			return lhs.absolute == rhs.absolute;
		}
		friend bool operator==(node_type const& lhs, boost::filesystem::path const& rhs) {
			return lhs.absolute == rhs;
		}
		friend bool operator==(boost::filesystem::path const& lhs, node_type const& rhs) {
			return lhs == rhs.absolute;
		}
		template<typename Elem, typename Traits>
		friend std::basic_ostream<Elem, Traits>& operator<<(std::basic_ostream<Elem, Traits>& lhs, node_type const& rhs) {
			return lhs << rhs.filename.generic_string();
		}
	};


	// グラフのエッジ
	typedef std::pair<int, int> edge_type;
	// グラフ型
	typedef boost::adjacency_list<
			boost::vecS,
			boost::vecS,
			boost::directedS,
			boost::no_property
		> graph_type;


public:


	explicit include_graph_hooks(boost::filesystem::path const& start)
		: node_list_(1, node_type(boost::filesystem::absolute(start), start.filename()))
		, current_(1, 0)
	{}

	// グラフを作成する関数
	template<typename Graph>
	Graph make_graph() const {
		return Graph(edge_list_.begin(), edge_list_.end(), node_list_.size());
	}
	// graphviz 形式で出力する関数
	void write_graphviz(std::ostream& out) const {
		boost::write_graphviz(
			out,
			make_graph<graph_type>(),
			boost::make_label_writer(&node_list_[0])
			);
	}


public:
	// インクルードファイル解析開始をフック
	template<typename Context>
	void opened_include_file(
		Context const& ctx,
		std::string const& relname, 
		std::string const& absname,
		bool is_system_include
		)
	{
		boost::filesystem::path abspath(boost::filesystem::absolute(absname));    // 絶対パス
		std::vector<node_type>::iterator found = std::find(node_list_.begin(), node_list_.end(), abspath);
		int to = std::distance(node_list_.begin(), found);                        // インクルードファイルのインデックス
		if (found == node_list_.end()) {                                        // 最初のインクルードならばノードに追加
			node_list_.push_back(
				node_type(abspath,
				abspath.filename())
				);
		}
		edge_list_.push_back(edge_type(current_.back(), to));                            // エッジに追加
		current_.push_back(to);                                                    // カレントを更新
	}
	// インクルードファイル解析完了をフック
	template<typename Context>
	void returning_from_include_file(Context const& ctx) {
		current_.pop_back();                                                    // カレントを戻す
	}

private:

	std::vector<node_type> node_list_;
	std::vector<edge_type> edge_list_;
	std::vector<int> current_;

};

int main(int argc, const char* argv[])
{
	using namespace boost::wave;

	try {
		// ファイル argv[1] の内容を全部 text に読み込む
		std::ifstream ifs( argv[1] );
		std::string text(
			std::istreambuf_iterator<char>(ifs.rdbuf()),
			std::istreambuf_iterator<char>()
			);
		
		// プリプロセッサを用意
		typedef context<
			std::string::iterator,
		cpplexer::lex_iterator<cpplexer::lex_token<> >,
		iteration_context_policies::load_file_to_string,
		include_graph_hooks                               // インクルードをグラフ化するフッククラスを使う
			> context_type;
		context_type ctx(text.begin(), text.end(), argv[1], include_graph_hooks(argv[1]));
		
		// オプションやマクロを設定
		ctx.set_language(
			language_support(
				support_cpp                                 // C++として処理
				| support_option_long_long                  // long long 型サポート
				| support_option_variadics                  // 可変長引数マクロサポート
				| support_option_include_guard_detection    // インクルードガード検出
			)
		);

		ctx.add_macro_definition("_WIN32");
		ctx.add_macro_definition("_DEBUG");
		ctx.add_macro_definition("_CONSOLE");

		ctx.add_sysinclude_path("C:/include/");
		ctx.add_sysinclude_path("C:/Program Files/Microsoft Visual Studio 9.0/VC/include");
//		ctx.add_sysinclude_path("/usr/local/include/c++/4.7.0");
//		ctx.add_sysinclude_path("/usr/local/include/c++/4.7.0/i686-pc-linux-gnu");
//		ctx.add_sysinclude_path("/usr/local/include/c++/4.7.0/backward");
//		ctx.add_sysinclude_path("/usr/local/lib/gcc/i686-pc-linux-gnu/4.7.0/include");
//		ctx.add_sysinclude_path("/usr/local/include");
//		ctx.add_sysinclude_path("/usr/local/lib/gcc/i686-pc-linux-gnu/4.7.0/include-fixed");
//		ctx.add_sysinclude_path("/usr/include");

		// プリプロセスを走らせる
		for (context_type::iterator_type it = ctx.begin(), last = ctx.end(); it != last; ++it) {
			//std::cerr << *it << std::endl;
		}

		// out.dot にグラフ出力
		{
			std::ofstream ofs("out.dot");
			ctx.get_hooks().write_graphviz(ofs);
		}

	} catch(cpp_exception& e) {
		// プリプロセスでエラー発生
		std::cerr << e.file_name() << "(" << e.line_no() << "):" << e.description() << std::endl;
	}
}

