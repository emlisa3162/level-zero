/*
 *
 * Copyright (C) 2024 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 */

#include "gtest/gtest.h"

#include "loader/ze_loader.h"
#include "ze_api.h"

namespace {

TEST(
    LoaderAPI,
    GivenLevelZeroLoaderPresentWhenCallingzeGetLoaderVersionsAPIThenValidVersionIsReturned) {

  EXPECT_EQ(ZE_RESULT_SUCCESS, zeInit(0));

  size_t size = 0;
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderGetVersions(&size, nullptr));
  EXPECT_GT(size, 0);

  std::vector<zel_component_version_t> versions(size);
  EXPECT_EQ(ZE_RESULT_SUCCESS, zelLoaderGetVersions(&size, versions.data()));

  std::cout << "Found " << versions.size() << " versions" << std::endl;
  std::cout << std::endl;
  const std::string loader_name = "loader";
  for (auto &component : versions) {
    std::cout << "component.component_name: " << component.component_name << std::endl;
    std::cout << "component.component_lib_version.major: " << component.component_lib_version.major << std::endl;
    std::cout << "component.spec_version: " << component.spec_version << std::endl;
    std::cout << "component.component_lib_name: " << component.component_name << std::endl;
    std::cout << std::endl;

    if (loader_name == component.component_name) {
      EXPECT_GE(component.component_lib_version.major, 1);
    }
  }
}

} // namespace
