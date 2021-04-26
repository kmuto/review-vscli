= Vivliostyleのテスト

Vivliostyleでビルドするテストです。

== 仕組み

@<tt>{rake vivliostyle}でVivliostyleによるPDFが生成されます。仕組み的には、EPUBを作った後に@<tt>{vivliostyle-cli}を呼び出し、PDF変換します。
