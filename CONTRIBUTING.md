## ブランチ名
Issue ID をそのままブランチ名とすることを推奨します。
ただし先頭の"#"は除去します。

(例) Issue ID: #10 → ブランチ名: 10

## コーディング規約
clang-format にてデフォルト設定のコード整形を行うことを推奨します。

```$ clang-format -i (cpp hpp ファイル)```

さらに cpplint で静的コードチェックをすることを推奨します。

```$ cpplint (cpp hpp ファイル)```

これらのコーディングチェックを自動化するには、[blue-hood/.git_template](https://github.com/blue-hood/.git_template) を導入してください。
