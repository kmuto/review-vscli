# Vivliostyle + Re:VIEW の制作プロジェクト例

このリポジトリは、Docker + Re:VIEW + Vivliostyle で CSS 組版を実現するプロジェクトの例です。Re:VIEW 形式の代わりに Markdown 形式で記述することもできます。

Re:VIEW、Vivliostyle、それに pandoc2review のセットを1から構築するのはそれなりに手間なので、Docker コンテナでの利用を推奨します。

## Docker

[Docker](https://www.docker.com/) および [docker-compose](https://docs.docker.com/compose/install/) を利用しています。

プロジェクト内で下記のコマンドを実行し、Docker イメージを作成します。

```
docker-compose build
```

- Docker イメージ vvakame/review をベースとしています。
- Linux 上で Docker を実行している場合、一時ファイルシステムの構成と Ruby のファイルコピー命令との組み合わせでファイルをうまくコピーできない現象があるため、Re:VIEW にパッチを当てています。(次期 Re:VIEW 5.2? で修正予定)
- Vivliostyle CLI (@vivliostyle/cli) および依存関係ライブラリパッケージ群をインストールしています。

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

## Markdownの利用
markdown.md に説明があります。catalog.yml に .md→.re とした名前で登録するほかは、特に注意を払うことなく Markdown 記法で記述できます。
