#!/bin/bash

set -o nounset
set -o pipefail
#set -o xtrace

TMP_DIR="/tmp"
CXX="g++ -std=c++17 -O3"
SCRIPT_DIR="$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
TEMPLATE_NAME=template.cpp
TEMPLATE=${SCRIPT_DIR}/${TEMPLATE_NAME}
TESTS_DIR_NAME=tests
TESTS_DIR=${SCRIPT_DIR}/${TESTS_DIR_NAME}
BUILD_DIR=
COLOR_BLACK=0
COLOR_RED=1
COLOR_GREEN=2
COLOR_YELLOW=3
COLOR_BLUE=4
COLOR_MAGENTA=5
COLOR_CYAN=6
COLOR_WHITE=7
OK=0
TOTAL=0
DEBUG=0

PROBLEMS="problem1 problem2 problem3 problem4 problem5 problem6 problem7 problem8 problem9"

function show_help() {
	cat > /dev/stdout << END
${0} [-p] [-h]
run all the tests

ARGUMENTS:
-d - debug mode, show your output and the desired one
-h - show help
END
}

function create_tmp_dir() {
    until [ -n "${BUILD_DIR}" -a ! -d "${BUILD_DIR}" ]
    do
        BUILD_DIR="${TMP_DIR}/competitive_programming_tests.${RANDOM}${RANDOM}${RANDOM}"
    done
    mkdir -p -m 0700 ${BUILD_DIR}  || { echo "FATAL: Failed to create temp dir '${BUILD_DIR}': $?"; cleanup; exit 1; }
    cp -r "${TESTS_DIR}" ${BUILD_DIR} || { echo "FATAL: Failed to create temp dir 'tests': $?"; cleanup; exit 1; }
    cp "${TEMPLATE}" ${BUILD_DIR} || { echo "FATAL: Failed to create temp dir 'template': $?"; cleanup; exit 1; }
}

function cleanup() {
    exec &> /dev/tty
    tput cnorm # cursor normal
    tput sgr0  # turn off all attributes
    rm -rf ${BUILD_DIR}
}

function println() {
    tput setaf ${1} # set color
    echo -e "${2}"
}

function print() {
    tput setaf ${1}
    echo -ne "${2}"
}

function space() {
    head -c ${1} < /dev/zero | tr '\0' ' '
}

function draw_bar() {
    tput bold
    for i in $(seq ${1})
    do
        print ${COLOR_BLUE} "\xe2\x80\x95" #"\u2015"
    done
    tput sgr0
}

function title() {
    draw_bar 6
    tput bold
    print ${COLOR_BLUE} "${1}"
    tput sgr0
    draw_bar 6
    echo
}

function test_problem() {
    println ${COLOR_WHITE} "$(space 1) Testing ${3}"
    local total=0
    local ok=0
    local res=${BUILD_DIR}/res.txt
    pushd "${1}" > /dev/null
    for file in ${3}.*.in
    do
        timeout 2s ${2} "${3}" < "${file}" > $res # 2> /dev/null
        if (($DEBUG == 1))
        then
            println ${COLOR_WHITE} "Your output \xf0\x9f\xa4\x9e"
            cat $res
            println ${COLOR_WHITE} "Correct output"
            cat ${file%in}out
        fi
        diff -Z -E $res ${file%in}out &> /dev/null
        if (($? == 0))
        then
            print ${COLOR_WHITE} "$(space 2)\xe2\x80\xa2" #\u2022"
            println ${COLOR_GREEN} "${file} \xe2\x9c\x94 " #\u2714 "
            ((ok++))
            ((OK++))
        else
            print ${COLOR_WHITE} "$(space 2)\xe2\x80\xa2" #\u2022"
            println ${COLOR_RED} "${file} \xe2\x9a\xa0 " #\u26a0 "
        fi
        ((total++))
        ((TOTAL++))
    done
    popd > /dev/null
    tput bold
    println ${COLOR_WHITE} "$(space 1)Summary: ${ok}/${total} PASSED"
    tput sgr0
}

function total() {
    echo
    title "TOTAL"
    tput bold
    println ${COLOR_WHITE} "$(space 1)${OK}/${TOTAL} PASSED"
    tput sgr0
}

trap "cleanup; exit 1" TERM INT QUIT

clear
tput civis # make cursor invisible
create_tmp_dir
while getopts "hd" opts
do
     case ${opts} in
         d)
             DEBUG=1
             break
             ;;
         h)
            show_help
            cleanup
            exit 1;;
     esac
done
pushd ${BUILD_DIR} > /dev/null
${CXX} ${TEMPLATE_NAME}
if (($? != 0))
then
    popd > /dev/null
    println ${COLOR_RED} "$(space 1) Compilation error on ${TEMPLATE}"
    cleanup
    exit 1
fi
popd > /dev/null
for problem in ${PROBLEMS}
do
    test_problem "${BUILD_DIR}/${TESTS_DIR_NAME}" "${BUILD_DIR}/a.out" ${problem}
done
total
cleanup
exit 0
