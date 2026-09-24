// A compilation unit for the hl5 container, which is otherwise header-only.
// Catapult synthesises translation units, so the top needs one of its own --
// the three stage .cpp files each include only their own header and would
// never bring hl5 into the design.
//
// It must live beside hl5.hpp: a quoted #include searches the including file's
// directory first, which is the same co-location rule the testbench sources
// follow (see README, "Build and run").
#include "hl5.hpp"
