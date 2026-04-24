load("@rules_qt//:qt.bzl", "qt_cc_binary", "qt_cc_library")

qt_cc_library(
    name = "lang_lib",
    srcs = [
        "src/main_window.cpp",
        "src/session_engine.cpp",
    ],
    hdrs = [
        "src/main_window.h",
        "src/session_engine.h",
        "src/exercises.h",
        "src/fuzzy_matcher.h",
        "src/style.h",
        "src/task_repository.h", # Новый файл здесь
    ],
    deps = [
        "@rules_qt//:qt_core",
        "@rules_qt//:qt_gui",
        "@rules_qt//:qt_widgets",
    ],
)

qt_cc_binary(
    name = "lang_app",
    srcs = ["src/main.cpp"],
    deps = [
        ":lang_lib",
        "@rules_qt//:qt_core",
        "@rules_qt//:qt_gui",
        "@rules_qt//:qt_widgets",
    ],
)
