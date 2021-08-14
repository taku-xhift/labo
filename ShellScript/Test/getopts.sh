#!/bin/sh
while getopts l:t: opt
do
  case ${opt} in
  l)
   LIST=${OPTARG};;
  t)
   TYPE=${OPTARG};;
  \?)
   exit 1;;
  esac
done
echo "LIST=${LIST}"
echo "TYPE=${TYPE}"
