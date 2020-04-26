//
// Copyright © 2020 osy86. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *kSkyLightPath = "/System/Library/PrivateFrameworks/SkyLight.framework/SkyLight";

typedef int32_t (*SLSSetDebugOptionsData_t)(uint32_t, void *, size_t);
const uint32_t kSLSDebugRefreshRate = 0x800000A7;

static SLSSetDebugOptionsData_t getSLFunction(void) {
    void *ctx = dlopen(kSkyLightPath, RTLD_NOW);
    if (!ctx) {
        return NULL;
    }
    void *sym = dlsym(ctx, "SLSSetDebugOptionsData");
    if (!sym) {
        dlclose(ctx);
        return NULL;
    }
    atexit_b(^{
        dlclose(ctx);
    });
    return (SLSSetDebugOptionsData_t)sym;
}

int main(int argc, const char * argv[]) {
    SLSSetDebugOptionsData_t SLSSetDebugOptionsData = getSLFunction();
    int32_t rate = 0;
    uint32_t res = 0;
    if (!SLSSetDebugOptionsData) {
        fprintf(stderr, "failed to find SLSSetDebugOptionsData\n");
        return 1;
    }
    if (argc < 3 || strcmp(argv[1], "-r") != 0) {
        fprintf(stderr, "usage: %s -r rate\n  -r    refreshes per second, 0 to disable\n", argv[0]);
        return 1;
    }
    rate = atoi(argv[2]);
    res = SLSSetDebugOptionsData(kSLSDebugRefreshRate, &rate, sizeof(rate));
    fprintf(stderr, "SLSSetDebugOptionsData: 0x%08X (%s)\n", res, res == 0 ? "success" : "failed");
    return 0;
}
