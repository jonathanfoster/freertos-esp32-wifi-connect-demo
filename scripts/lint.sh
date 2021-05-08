#!/usr/bin/env bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"

echo "--------------------------"
echo "-- Running clang-format --"
echo "--------------------------"
clang-format --dry-run --style=file "$DIR"/../src/**
echo ""

echo "--------------------------"
echo "-- Running clang-tidy --"
echo "--------------------------"
clang-tidy --format-style=file -p="$DIR"/../build "$DIR"/../src/**
echo ""

echo "------------------------"
echo "-- Running shellcheck --"
echo "------------------------"
echo ""
shellcheck "$DIR"/**
