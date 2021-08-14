

# 二重定義が見つかった場合の例外
class DoubleDefineError < StandardError;
end

# 型定義が見つからなかった場合の例外
class TypeUnDefindError < StandardError;
end

# 構文エラー
class SyntaxFormatError < StandardError;
end

# case 文や if 文で見つからなかった場合のもの
class UnMatchError < StandardError;
end

# 全角スペースを使用していた場合の例外
class UseDoubleByteSpaceError < StandardError;
end

# 引数に何も指定が無かった場合のエラー
class NoArgumentError < StandardError;
end

# 指定されたファイルが存在しなかった場合
class NoFileError < StandardError;
end


