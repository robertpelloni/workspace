
            include("${CMAKE_CURRENT_LIST_DIR}/GWEN_openglTargets.cmake")
            set_property(
                TARGET GWEN_opengl
                APPEND PROPERTY
                    INTERFACE_INCLUDE_DIRECTORIES "C:/Users/hyper/workspace/okgame/lib/GWEN/gwen"
            )
        