#pragma once
#include "parser.h"
#include <vector>
#include <memory>

void renameRegisters(vector<unique_ptr<LineBase>>& instructions);
