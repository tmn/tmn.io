#!/usr/bin/env bash

article_files=()

while IFS= read -r -d $'\0'; do
    article_files+=("$REPLY")
done < <(find src/www -name "*.md" -print0)

IFS=$'\n' article_files=($(sort -r <<< "${article_files[*]}"))
unset IFS

./_build/src/builder/builder ${article_files[@]}
