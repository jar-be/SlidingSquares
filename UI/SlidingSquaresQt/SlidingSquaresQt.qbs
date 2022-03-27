import qbs.FileInfo

Project {

    QtApplication {
        Depends {
            name: "Qt.widgets"
        }

        Depends {
            name: "SlidingSquaresLib"
        }

        cpp.defines: [// You can make your code fail to compile if it uses deprecated APIs.
            // In order to do so, uncomment the following line.
            "QT_DISABLE_DEPRECATED_BEFORE=0x060000" // disables all the APIs deprecated before Qt 6.0.0
        ]

        files: ["main.cpp", "mainwindow.cpp", "mainwindow.h", "mainwindow.ui"]

        install: true
        installDir: qbs.targetOS.contains("qnx") ? FileInfo.joinPaths(
                                                       "/tmp", name,
                                                       "bin") : base
    }

    StaticLibrary {
        name: "SlidingSquaresLib"
        Depends {
            name: "cpp"
        }
        files: ["lib/CBoard.h"]
    }

    CppApplication {
        name: "SlidingSquaresConsole"
        consoleApplication: true
        files: "console/main.cpp"
        Depends {
            name: "SlidingSquaresLib"
        }

        Group {
            // Properties for the produced executable
            fileTagsFilter: "application"
            qbs.install: true
            qbs.installDir: "bin"
        }
    }
}
