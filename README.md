# SDL2project_Test

練習使用SDL2函式庫製作我想要的圖表功能

</br>

## 環境的建構

* 要進行編譯之前的準備工作  

此專案是在Windows環境運行，需要安裝MinGW的編譯套件，運用gcc編譯工具進行編譯，並去SDL2官網下載函式庫  
以便編譯時鏈結到SDL2函式庫

* 首先`git clone`本專案並放在某目錄 **_~/SDL2project_Test/_**    

</br>

### SDL2函式庫下載

* 去SDL2官網下載此檔案 `SDL2-devel-<version>-mingw.zip`

### 64位元MinGW

* 確認gcc的版本應該要如下顯示

`gcc -v` 

```
COLLECT_GCC=C:\MinGW\bin\gcc.exe  
```

* 將`SDL2-devel-<version>-mingw.zip`解壓縮
* 創立資料夾 **_SDL2src_** 在本專案資料夾中 **_~/SDL2project_Test/_**
* 在解壓縮後的資料夾 `SDL2-<version>`中 ，把 **_x86_64-w64-mingw32_** 下的 **_include_** 與 **_lib_** 複製到 **_SDL2src_** 底下
* 把 **_bin_** 中的 `SDL2.dll` 複製到 **_~/SDL2project_Test/_** 下

### 32位元MinGW

* 確認gcc的版本應該要如下顯示

`gcc -v` 

```
COLLECT_GCC=C:\MinGW\bin\gcc.exe  
COLLECT_LTO_WRAPPER=c:/mingw/bin/../libexec/gcc/mingw32/9.2.0/lto-wrapper.exe  
Target: mingw32  
Thread model: win32  
gcc version 9.2.0 (MinGW.org GCC Build-2)  
```

* 將`SDL2-devel-<version>-mingw.zip`解壓縮
* 創立資料夾 **_SDL2src_** 在本專案資料夾中 **_~/SDL2project_Test/_**
* 在解壓縮後的資料夾 `SDL2-<version>`中 ，把 **_i686-w64-mingw32_** 下的 **_include_** 與 **_lib_** 複製到 **_SDL2src_** 底下
* 把 **_bin_** 中的 `SDL2.dll` 複製到 **_~/SDL2project_Test/_** 下

經過上述步驟後應該能成功的建構編譯的環境了

## 編譯

執行 **_~/SDL2project_Test/_** 下的 `make.bat`   
會創立 **_out/_** 資料夾，編譯後的 `make.exe` 執行檔會在其中  



