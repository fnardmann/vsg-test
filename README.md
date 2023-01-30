## Hello World project for VulkanSceneGraph
The `teapot.vsgt` file comes in the original from the [vsgExamples](https://github.com/vsg-dev/vsgExamples/tree/master/data/models) project.
  
### Installation (Linux)
```
https://packages.lunarg.com/#

# Ubuntu 20.04 - vulkan 1.3.231
wget -qO - https://packages.lunarg.com/lunarg-signing-key-pub.asc | sudo apt-key add -
sudo wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.3.231-focal.list https://packages.lunarg.com/vulkan/1.3.231/lunarg-vulkan-1.3.231-focal.list
sudo apt update
sudo apt install vulkan-sdk
```
  
### Run
```shell
mkdir build
cd build
cmake ..
make
./main
```

![Screenshot from 2023-01-30 19-32-15](https://user-images.githubusercontent.com/59708022/215564559-bfa68143-a6ce-4f70-bee4-aa4e1d080c20.png)
