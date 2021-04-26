= 章見出し
//lead{
章にはリードが入ることがあります。図版や表が入ることはまずありませんが、@<b>{太字}くらいは使われることも。

複数段落になる可能性もあります。
//}

段落は普通に書き連ねていくだけです。段落間は空行を含めます。

こんなかんじ

です。空けない場合は、1つの
段落として結合されます。TeXと違って文字種によって良い塩梅にスペースを入れてくれたりはしないので、特に英文の場合は注意が必要です。this is a
pen.と「apen」になってしまいます。行頭行末のスペース文字も詰められてしまうので、
this is a pen.は途中改行せずに記述しなければなりません (config.yml で @<tt>{join_lines_by_lang: true} とすると、unicode-eaw ライブラリによる言語判定でのスペース挿入もできます)。

通常段落は「字下げ」することを想定して表現されますが、たとえばコードをまたぐ

//emlist[][ruby]{
'hello!' 'こんにちはWorld!'
//}

//noindent
ようにしたい場合は、またいだ後の段落前に「@<tt>{//noindent}」を入れておくことで字下げを抑止できます。

強制的に空行を作りたいときには@<tt>{//blankline}を使います。

//blankline
//blankline
//blankline

3行アキを入れました。


== 節見出し
@<tt>{=}の数で見出しレベルを表しますが、最大@<tt>{=====}の5レベルまでの見出しがあり得ます。

 * @<tt>{=}：章および部
 * @<tt>{==}：節
 * @<tt>{===}：項
 * @<tt>{====}：段
 * @<tt>{=====}：レベル5見出し

「X.X.X」のように採番するか否かは@<tt>{config.yml}の@<tt>{secnolevel}パラメータで変動します。

また、nonumあるいはnotocを付けた見出しは、章であっても採番されません。前者nonumは採番なし・目次に含める、後者notocは採番なし・目次にも含めないという意味です。

===[nonum] 採番しない項見出し

=== 採番する項見出し

nodispを付けると、紙面には表示されず目次には含まれる見出しとなります（採番なし）。節以下のレベルで使うことはほとんどなく、たとえば「献辞」のように紙面には見出しを出したくないけれども目次には入れておきたい前付名などに使うことを想定しています。

===[nodisp] nodispで隠れた見出し

== 箇条書き
=== ナカグロ箇条書き
ナカグロ箇条書き（HTMLの@<i>{ul}、TeXの@<i>{itemize}）は@<i>{スペース}+@<tt>{*}+@<i>{スペース}で表現します。インラインタグが含まれることがあります。

 * 箇条書き1
 * 箇条書き2@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}

入れ子ナカグロ箇条書きもあります。

 * 箇条書き1
 ** 箇条書き1-1
 ** 箇条書き1-2
 *** 箇条書き1-2-1
 * 箇条書き2
 ** 箇条書き2-1

箇条書きの間に別の要素（ぶらさがりの段落など）が入る場合、@<tt>{//beginchild} と @<tt>{//endchild} で囲むことで入れ子を表現可能です。濫用は避けてください。

=== 番号箇条書き
番号箇条書き（HTMLの@<i>{ol}、TeXの@<i>{enumerate}）は@<i>{スペース}+@<tt>{数字.}+@<i>{スペース}で表現します。

 1. 箇条書き1
 2. 箇条書き2@<b>{太字bold}@<tt>{等幅code}

=== 用語リスト
用語リスト（HTMLの@<i>{dl}、TeXの@<i>{description}）は@<i>{スペース}+@<tt>{:}+@<i>{スペース}で見出しを、説明は行頭にタブかスペースを入れて表現します。

 : Alpha@<b>{bold太字}@<i>{italicイタ}@<tt>{等幅code}
	@<i>{DEC}の作っていた@<b>{RISC CPU}。@<i>{italicイタ}@<tt>{等幅code}
	浮動小数点数演算が速い。
 : POWER
	IBMとモトローラが共同製作したRISC CPU。@<br>{}
	派生としてPOWER PCがある。
 : SPARC
	Sunが作っているRISC CPU。
	CPU数を増やすのが得意。

== ブロック命令
=== ソースコード
採番付きリストの場合はlistです（@<list>{list2-1}）。

//list[list2-1][@<b>{Ruby}の@<tt>{hello}コード][ruby]{
puts 'Hello, World!'
//}

行番号と採番付きのリストはlistnumです。

//listnum[list2-2][行番号はリテラルな文字で特に加工はしていない][ruby]{
class Hello
  def initialize
    @msg = 'Hello, World!'
  end
end
//}

採番なしはemlistを使います。キャプションはあったりなかったりします。

//emlist[][c]{
printf("hello");
//}

//emlist[Python記法][python]{
print('hello');
//}

行番号付きのパターンとしてemlistnumがあります。

//emlistnum[][c]{
printf("hello");
//}

//firstlinenum[101]
//emlistnum[Python記法][python]{
print('hello');
//}

ソースコード引用を主ターゲットにするにはsourceというのを用意しています。

//source[hello.rb][ruby]{
puts 'Hello'
//}

実行例を示すとき用にはcmdを用意しています。いずれにせよ、商業書籍レベルでは必要なので用意しているものの、原稿レベルで書き手が使うコードブロックはほどほどの数に留めておいたほうがよいのではないかと思います。TeX版の紙面ではデフォルトは黒アミ。印刷によってはベタ黒塗りはちょっと怖いかもなので、あまり長々したものには使わないほうがいいですね。

//cmd{
$ @<b>{ls /}
//}

=== 図
採番・キャプション付きの図の貼り付けはimageを使用します（@<img>{ball}）。図版ファイルは識別子とビルダが対応しているフォーマットから先着順に探索されます。詳細については@<href>{https://github.com/kmuto/review/wiki/ImagePath, ImagePath}のドキュメントを参照してください。

//image[ball][ボール]{
//}

採番なし、あるいはキャプションもなしのものはindepimageを使います。

//indepimage[logic]{
//}

//indepimage[logic2][採番なしキャプション]{
//}

=== 表
表はtableを使います。

//table[tab2-1][表の@<b>{例}]{
A	B	C
----------------------------------
D	E@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}	F@<br>{}G
H	I	長いセルの折り返し■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□■□
//}

採番はしたくないけれどもキャプションは指定したいという場合はemtableがあります。

//emtable[キャプションを指定したいが採番はしたくない表]{
A	B
C	D
//}

画像にしておいて貼り付けたほうがよさそうな場合はimgtableを使います（@<table>{table}）。

//imgtable[table][ポンチ表]{
//}

=== 囲み記事
@<embed>{/}/{〜//}の囲み記事の中には段落のみしか入らないものと想定します（箇条書きなどを入れたい場合はユーザーの責任で適宜、変換後ソースを加工してもらうことを前提とします）。

引用はquoteで表現します。上下アキ、左インデント（2文字くらい？）が入るのが一般的でしょうか。

//quote{
ここに引用文。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}

2行目の引用文。
//}

中寄せはcenteringです。

//centering{
中寄せ本文。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}

2行目の中寄せ本文。
//}

右寄せはflushrightです。

//flushright{
右寄せ本文。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}

2行目の右寄せ本文。
//}

ノートnote。以降、キャプションあり/なしのパターンがあります。表現については結局紙面デザインに応じて千差万別になるものだと思いますので、基本デザインとしては何か囲み要素だとわかって、カスタマイズしやすければよい、という程度です。

//note[ノートの例@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}]{
ノート1。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}

ノート2。
//}

//note{
ノート。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}
//}

メモmemo。

//memo[メモの例@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}]{
メモ1。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}

メモ2。
//}

//memo{
メモ。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}
//}

Tips tip。

//tip[Tipsの例@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}]{
Tips1。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}

Tips2。
//}

//tip{
Tips。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}
//}

情報 info。

//info[情報の例@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}]{
情報1。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}

情報2。
//}

//info{
情報。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}
//}

注意 warning。

//warning[注意の例@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}]{
注意1。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}

注意2。
//}

//warning{
注意。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}
//}

重要 important。

//important[重要の例@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}]{
重要1。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}

重要2。
//}

//important{
重要。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}
//}

警告 caution。

//caution[警告の例@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}]{
警告1。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}

警告2。
//}

//caution{
警告。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}
//}

注意 notice。

//notice[注意の例@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}]{
注意1。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}

注意2。
//}

//notice{
注意。@<b>{太字bold}@<i>{italicイタ}@<tt>{等幅code}
//}

== インライン命令
//label[inlineop]

=== 書体
本文での……キーワード@<kw>{キーワード, keyword}、太字@<b>{b太字}、イタリック@<i>{iイタリック}、等幅@<tt>{tt等幅}、強調@<strong>{strong強調}、強調@<em>{em強調}、下線@<u>{u下線}、等幅@<code>{code等幅}、等幅太字@<ttb>{ttb等幅太字}、等幅イタリック@<tti>{tti等幅イタリック}、網カケ@<ami>{amiアミ}、挿入@<ins>{ins挿入}、削除@<del>{del削除}、16進UTF文字指定@<uchar>{3042}

#@# 傍点@<bou>{bou傍点}
ルビ@<ruby>{愕然, がくぜん}
#@#縦中横@<tcy>{90}
