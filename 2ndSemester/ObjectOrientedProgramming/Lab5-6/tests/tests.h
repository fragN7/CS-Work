//
// Created by Alen on 16/03/2022.
//

#include "../array/Array.h"
#include "../errors/exceptions.h"
#include "../repo/repository.h"
#include "../service/service.h"
#include "../validation/validation.h"
#include <cassert>
#include <sstream>
#pragma once

class Testing {

private:
    static void test_array();
    static void test_domain();
    static void test_repo();
    static void test_service();
    static void test_validation();

public:
    Testing () = default;
    static void run_tests();
    ~Testing();
};