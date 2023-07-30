#!/usr/bin/env bash

article_files=()

while IFS= read -r -d $'\0'; do
    article_files+=("$REPLY")
done < <(find src/www -name "*.md" -print0)

./_build/src/builder/builder ${article_files[@]}

cp -r src/www/assets _dist/
