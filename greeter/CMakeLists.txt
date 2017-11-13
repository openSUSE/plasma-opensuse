cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(QT_MIN_VERSION "5.2.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

include(FeatureSummary)
include(WriteBasicConfigVersionFile)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Gui Xml)
find_package(KF5 REQUIRED COMPONENTS KDELibs4Support)

set(greeter_SRCS main.cpp greetings.cpp)

kde4_add_executable(SUSEgreeter ${greeter_SRCS})

target_link_libraries(SUSEgreeter ${KDE4_KDEUI_LIBS} ${QT_QTXML_LIBRARY})

install(TARGETS SUSEgreeter DESTINATION ${BIN_INSTALL_DIR})

install( FILES greet_header.html greet_section.html greet_footer.html greet.xml
         DESTINATION ${DATA_INSTALL_DIR}/SUSEgreeter )

install(FILES SUSEgreeter.desktop DESTINATION ${AUTOSTART_INSTALL_DIR})

install( FILES SUSEgreeter.desktop DESTINATION  ${XDG_APPS_INSTALL_DIR} )

add_subdirectory( pics )
