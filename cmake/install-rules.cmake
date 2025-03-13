install(
    TARGETS Jengine_exe
    RUNTIME COMPONENT Jengine_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
