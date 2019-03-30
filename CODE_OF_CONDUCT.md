# Code of Conduct

## 目標
SynthCore はシンセサイザーのシミュレーションを行うモジュールです。シンセサイザーの配線、シミュレーションの開始等はコマンドで行います。イメージとして、以下のようなコマンドを打つと 440 Hz の正弦波が再生されます。

```
> addcom Sine    # 正弦波部品を追加
{"uuid", "cb367e6c-e029-434f-99c4-800e71af22b0"}
> addcom Input    # パラメータ入力部品を追加
{"uuid", "5443b274-39c1-4667-92de-3f1a47e90edb"}
> addcom Speaker    # スピーカーを追加
{"uuid", "753bdad7-f3fa-4385-9837-c9389914c98c"}

> lspin cb367e6c-e029-434f-99c4-800e71af22b0    # 正弦波部品の入力ポートを一覧表示
{"freq": "6291ef1c-c040-498b-9278-a669b37f9f5d"}
> lspout 5443b274-39c1-4667-92de-3f1a47e90edb    # パラメータ入力部品の出力ポートを一覧表示
{"value": "5c71ad5b-51ef-4524-b9b4-f96536edc0fc"}

> connect 5c71ad5b-51ef-4524-b9b4-f96536edc0fc 6291ef1c-c040-498b-9278-a669b37f9f5d    # 「パラメータ入力部品の値出力」と「正弦波部品の周波数入力」を接続
{}

> (…省略…)

> call 5443b274-39c1-4667-92de-3f1a47e90edb setvalue 440    # パラメータ入力部品の拡張コマンド setvalue を呼び出し、440 Hz をセット。
{}

> play    # 再生
```

このようなイメージでシンセサイザーを構築していきます。

## SynthCore の立ち位置
SynthCore はシンセサイザーシミュレータの基幹機能のみを提供します。よって、コマンドラインを直接操作することは想定せず、UUID でシンセサイザーの各部品を選択します。SynthCore への入力はコマンドライン引数をまとめた JSON、SynthCore からの出力は任意形式の JSON です。

先ほどの操作例でコマンドラインを操作していましたが、シェルプログラム（SynthShell）がユーザーと SynthCore を仲介しています。煩雑な UUID を使わずに以下のようなシンプルなコマンド構文にするならば、

`connnect Input1.value Sine.freq    # 煩雑な UUID を使用しない`

エイリアス（ここでは Input1.value と Sine.freq）を UUID に置き換えて SynthCore にコマンドを投げるように、SynthShell の機能を拡張します。よって、シンセサイザーとして最低限の基幹機能はSynthCore、CUI 機能は SynthShell として別々に開発します。

## きっかけ
SynthCore は、元々 blue-hood/WebToySynth リポジトリ内で開発していました。WebToySynth は Web ブラウザ上の JavaScript で動作するシンセサイザーでしたが、部品を20~30個配置するだけで処理落ちが顕著に現れました。そこで、シンセサイザーの基幹となる信号伝搬シミュレーションのプログラムのみを C++ で書き起こし、WebAssembly を使うことで実用的な処理速度を確保しました。しかし、GUIとシミュレーションプログラムが密結合（モジュールとして分離していない）していたため、JavaScript と WebAssembly の連携が困難でした。

そこで、C++ に移植したシミュレーションプログラムを SynthCore として独立し、WebToySynth の UI とうまく連携できるようにインタフェースを整備することにしました。リクエストを JSON で送信し、レスポンスを JSON で受け取る REST API を模したというわけです。

## 活用方法
前述の WebToySynth のバックグラウンドに組み込むことを想定しているほか、別のことにも応用できるかもしれません。SynthCore 自体は低レイヤーな信号伝搬シミュレータなので、シンセサイザーに限らず汎用的な制御システムを構築可能です。GUI の実装しだいで別種のアプリケーションを構築できるかもしれませんが、そこはアイデア次第です。

シンセサイザーシミュレータで3秒タイマーを構築する例
https://troopa.bluehood.net//?src=community%2Ftimer.syn