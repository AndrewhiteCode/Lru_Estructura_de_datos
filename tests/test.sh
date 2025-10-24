#!/usr/bin/env bash
set -e
DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="${DIR}/.."
BIN="${ROOT}/bin/lru"

if [ ! -x "${BIN}" ]; then
  echo "Binary not found. Run: make"
  exit 1
fi

OUT="$(mktemp)"
"${BIN}" < "${DIR}/sample.in" > "${OUT}"
diff -u "${DIR}/expected.out" "${OUT}" && echo "All tests passed."
rm -f "${OUT}"
