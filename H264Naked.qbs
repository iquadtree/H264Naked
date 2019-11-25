import qbs

CppApplication {
    name: "H264Naked"

    Depends { name: "cpp" }
    Depends {
        name: "Qt"
        submodules: ["core", "gui", "widgets"]
    }

    cpp.cxxLanguageVersion: "c++14"

    cpp.includePaths: [project.sourceDirectory + "/h264bitstream-0.1.9"]
    cpp.libraryPaths: [project.sourceDirectory + "/h264bitstream-0.1.9/.libs"]
    cpp.staticLibraries: ["h264bitstream"]

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
