# Re:VIEW + Vivliostyle の制作プロジェクト例

このリポジトリは、Docker + Re:VIEW + Vivliostyle で CSS 組版を実現するプロジェクトの例です。Re:VIEW 形式の代わりに Markdown 形式で記述することもできます。

## これは何をするものか
Re:VIEW + Vivliostyle での CSS 組版、および Markdown 変換の基本部分を設定済みの Re:VIEW プロジェクトを提供します。Docker イメージの利用により、(Dokcer と docker-compose をセットアップしておけば) 環境構築の手間いらずで PDF を作成できます。

CSS 組版に限らず、TeX PDF 生成環境も含んでいるので、一般的な TeX 組版、あるいは EPUB や InDesign XML、プレインテキストの作成といったことにももちろん利用できます。

## プロジェクトの使い方
基本的な Re:VIEW の使い方に準じています。

1. `git clone https://github.com/kmuto/review-vscli.git` でプロジェクトを展開します。
2. re 拡張子のコンテンツファイルを作って Re:VIEW マークアップで記述します (Markdown については後述)。
3. 目次の catalog.yml に登録します。
4. rake コマンドで変換します。rake epub, rake pdf, rake vivliostyle など

config.yml で書名などのメタ情報を変更できます。

サンプルとして、以下の3つのコンテンツファイルを用意し、catalog.yml に登録しています。実際の利用では catalog.yml から外してください。

- vscli.re : ごく短い Re:VIEW コンテンツサンプル
- syntax.re : Re:VIEW マークアップのサンプル (Re:VIEW の samples/syntax-book から抜粋)
- markdown.md : Markdown のサンプル

ほかに次のファイルがあります。

- config.yml : 基本設定ファイル
- config-vscli.yml : Vivliostyle 変換用の追加設定ファイル
- catalog.yml : カタログファイル
- doc : Re:VIEW のドキュメント
- images : 画像ファイル
- fonts : Vivliostyle 用のフォントファイル
- bundle.css : Vivliostyle 用のスタイルシートファイル
- style.css : EPUB, Web 用のスタイルシートファイル
- 00review-vivliostyle.pdf : Vivliostyle 変換サンプル
- Rakefile, lib : rake コマンドルール
- sty : TeX 用のファイル
- Dockerfile, docker-compose.yml : Docker 用の設定ファイル
- patches : Docker 内の Re:VIEW に適用するパッチファイル
- Gemfile : bundler 環境用の設定ファイル
- LICENSE : ライセンスファイル

### Markdownの利用

catalog.yml に .md→.re とした名前で登録するほかは、特に注意を払うことなく Markdown 記法で記述できます。

サンプルの markdown.md に説明があるので参照してください。

## Dockerでの利用法
Re:VIEW、Vivliostyle、それに pandoc2review (Markdown 変換) のセットを1から構築するのはそれなりに手間なので、Docker コンテナでの利用を推奨します。

[Docker](https://www.docker.com/) および [docker-compose](https://docs.docker.com/compose/install/) を利用するのがよいでしょう。

プロジェクト内で下記のコマンドを実行し、Docker イメージを作成します。

```
docker-compose build
```

- Docker イメージ [vvakame/review](https://hub.docker.com/r/vvakame/review) をベースとしています。
- Linux 上で Docker を実行している場合、一時ファイルシステムの構成と Ruby のファイルコピー命令との組み合わせでファイルをうまくコピーできない現象があるため、Re:VIEW にパッチを当てています。(次期 Re:VIEW 5.2? で修正予定)
- [Vivliostyle CLI](https://github.com/vivliostyle/vivliostyle-cli) (@vivliostyle/cli) および依存関係ライブラリパッケージ群をインストールしています。

### コンパイル (macOS、Linux の場合)
Vivliostyle による変換は、以下のように実行します。

```
docker-compose run -u `id -u` -e REVIEW_CONFIG_FILE=config-vscli.yml --rm review rake vivliostyle
```

ほかの変換も同様です。
```
docker-compose run -u `id -u` --rm review rake pdf    (TeX PDF)
docker-compose run -u `id -u` --rm review rake epub   (EPUB)
docker-compose run -u `id -u` --rm review rake clean  (ビルドファイル消去)
```

### コンパイル (Windows の場合)
★TBD

## CSSの切り分け
EPUB 用にはデフォルトの style.css を、Vivliostyle 用には [Vivliostyleで本を作ろう Vol.4のテーマ](https://github.com/vivliostyle/vivliostyle_doc/tree/gh-pages/ja/vivliostyle-user-group-vol4/themes/packages/theme) の bundle.css を利用しています。

このために、config-vscli.yml を別途用意し、docker-compose のビルド時に環境変数 `REVIEW_CONFIG_FILE` を渡してデフォルトの config.yml の代わりに読み込むようにします。

## ライセンス
- ほぼすべてのファイル : MIT License
- bundle.css : CC (Creative Commons) 0 (いかなる権利も保有しない)
