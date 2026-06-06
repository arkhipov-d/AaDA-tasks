#!/usr/bin/env bash
set -euo pipefail

workdir="$(mktemp -d)"
trap 'rm -rf "$workdir"' EXIT

cat > "$workdir/small.csv" <<'CSV'
a1,a2,b
2,1,5
1,-1,1
CSV

cat > "$workdir/small_expected.csv" <<'CSV'
x
2.0000000000
1.0000000000
CSV

./gauss "$workdir/small.csv" "$workdir/small_actual.csv"
cmp "$workdir/small_expected.csv" "$workdir/small_actual.csv"

cat > "$workdir/swap.csv" <<'CSV'
a1,a2,b
0,2,4
1,1,3
CSV

cat > "$workdir/swap_expected.csv" <<'CSV'
x
1.0000000000
2.0000000000
CSV

./gauss "$workdir/swap.csv" "$workdir/swap_actual.csv"
cmp "$workdir/swap_expected.csv" "$workdir/swap_actual.csv"

echo "Integration tests passed"
