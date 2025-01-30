D:\VulkanSDK\1.3.296.0\Bin\glslc.exe lattice_shader.vert -o lattice_shader.vert.spv
D:\VulkanSDK\1.3.296.0\Bin\glslc.exe lattice_shader.frag -o lattice_shader.frag.spv

copy /b  lattice_shader.vert.spv ..\..\x64\Debug\shaders\lattice_shader.vert.spv
copy /b  lattice_shader.vert.spv ..\..\x64\Release\shaders\lattice_shader.vert.spv

copy /b  lattice_shader.frag.spv ..\..\x64\Debug\shaders\lattice_shader.frag.spv
copy /b  lattice_shader.frag.spv ..\..\x64\Release\shaders\lattice_shader.frag.spv

D:\VulkanSDK\1.3.296.0\Bin\glslc.exe polygon_shader.vert -o polygon_shader.vert.spv
D:\VulkanSDK\1.3.296.0\Bin\glslc.exe polygon_shader.frag -o polygon_shader.frag.spv

copy /b  polygon_shader.vert.spv ..\..\x64\Debug\shaders\polygon_shader.vert.spv
copy /b  polygon_shader.vert.spv ..\..\x64\Release\shaders\polygon_shader.vert.spv
		 
copy /b  polygon_shader.frag.spv ..\..\x64\Debug\shaders\polygon_shader.frag.spv
copy /b  polygon_shader.frag.spv ..\..\x64\Release\shaders\polygon_shader.frag.spv

D:\VulkanSDK\1.3.296.0\Bin\glslc.exe point_light.vert -o point_light.vert.spv
D:\VulkanSDK\1.3.296.0\Bin\glslc.exe point_light.frag -o point_light.frag.spv

copy /b point_light.vert.spv ..\..\x64\Debug\shaders\point_light.vert.spv
copy /b point_light.vert.spv ..\..\x64\Release\shaders\point_light.vert.spv

copy /b point_light.frag.spv ..\..\x64\Debug\shaders\point_light.frag.spv
copy /b point_light.frag.spv ..\..\x64\Release\shaders\point_light.frag.spv

pause