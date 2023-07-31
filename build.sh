#!/usr/bin/env bash

echo -e "\n> Create _dist/ directory"
if [[ ! -d "_dist" ]]; then
   mkdir "_dist"
fi

article_files=()

while IFS= read -r -d $'\0'; do
    article_files+=("$REPLY")
done < <(find src/www -name "*.md" -print0)

IFS=$'\n' article_files=($(sort -r <<< "${article_files[*]}"))
unset IFS

./_build/src/builder/builder ${article_files[@]}

echo -e "\n> Copy assets to _dist/"
echo "-- Copying assets.."
cp -r src/www/assets _dist/
echo "-- Copying img.."
cp -r src/www/img _dist/

echo -e "\n> Build finished\n"
