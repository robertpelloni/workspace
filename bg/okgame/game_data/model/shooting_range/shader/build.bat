"%SCE_ORBIS_SDK_DIR%\host_tools\bin\orbis-wave-psslc.exe" -profile sce_vs_vs_orbis bg_shader_v.pssl -o bg_shader_v.sb
"%SCE_ORBIS_SDK_DIR%\host_tools\bin\orbis-wave-psslc.exe" -profile sce_ps_orbis    bg_shader_f.pssl -o bg_shader_f.sb
"%SCE_ORBIS_SDK_DIR%\host_tools\bin\orbis-wave-psslc.exe" -profile sce_vs_vs_orbis texture_shader_v.pssl -o texture_shader_v.sb
"%SCE_ORBIS_SDK_DIR%\host_tools\bin\orbis-wave-psslc.exe" -profile sce_ps_orbis    texture_shader_f.pssl -o texture_shader_f.sb
pause