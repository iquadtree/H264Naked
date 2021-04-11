import qbs

CppApplication {
    name: "H264Naked"

    Depends { name: "cpp" }
    Depends {
        name: "Qt"
        submodules: ["core", "gui", "widgets"]
    }

    property int cacheSize: 20480

    cpp.cxxLanguageVersion: "c++17"

    cpp.includePaths: [project.sourceDirectory + "/deps/h264bitstream"]
    cpp.libraryPaths: [project.sourceDirectory + "/deps/h264bitstream/.libs"]
    cpp.staticLibraries: [":libh264bitstream.a"]
    cpp.defines: ["CACHE_SIZE=" + cacheSize]

    Depends {
        condition: qbs.targetOS.contains("macosx")
        name: "ib"
    }

    Group {
        name: "Source Files"
        files: [
            "main.cpp",
            "MainWindow.cpp",
            "H264NALListModel.cpp"
        ]
    }

    Group {
        name: "Include Files"
        files: [
            "H264NALListModel.hpp",
            "MainWindow.hpp",
        ]
    }

    Group {
        name: "Ui Files"
        files: ["mainwindow.ui"]
    }

    Group {
        name: "Icons"
        condition: qbs.targetOS.contains("macosx")
        files: ["H264Naked.icns"]
        bundle.infoPlist: ({"CFBundleIconFile": "H264Naked"})
    }

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
