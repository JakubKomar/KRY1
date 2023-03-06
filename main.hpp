
#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

#include "break.hpp"
#include "config.hpp"
#include "encrypt.hpp"
#include "decrypt.hpp"

int main(int argc, char *argv[]);
config parseArgs(int argc, char *argv[]);
void cheackConf(config * cnf);

