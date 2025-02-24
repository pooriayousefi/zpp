#include <stdexcept>
#include <exception>
#include <iostream>
#include <unordered_map>
#include <utility>
int main(int argc, char *argv[])
{
    std::cout << "\nproject root path? ";
    std::string project_root_path{};
    std::cin >> project_root_path;

    std::unordered_map<size_t, std::string> targets{};
    targets.emplace(std::make_pair(1, "x86_64-unknown-linux-gnu"));
    targets.emplace(std::make_pair(2, "armv7-unknown-linux-gnueabihf"));    
    targets.emplace(std::make_pair(3, "x86_64-unknown-linux-musl"));
    targets.emplace(std::make_pair(4, "arm64-unknown-linux-gnu"));
    targets.emplace(std::make_pair(5, "aarch64-apple-darwin"));
    targets.emplace(std::make_pair(6, "x86_64-apple-darwin"));
    targets.emplace(std::make_pair(7, "i686-pc-windows-msvc"));
    targets.emplace(std::make_pair(8, "x86_64-pc-windows-msvc"));
    std::cout 
        << "\ntarget platforms:"
        << "\nx86_64-unknown-linux-gnu ---> 1" 
        << "\narmv7-unknown-linux-gnueabihf ---> 2" 
        << "\nx86_64-unknown-linux-musl ---> 3" 
        << "\narm64-unknown-linux-gnu ---> 4" 
        << "\naarch64-apple-darwin ---> 5" 
        << "\nx86_64-apple-darwin ---> 6" 
        << "\ni686-pc-windows-msvc ---> 7" 
        << "\nx86_64-pc-windows-msvc ---> 8" 
        << "\nbuild target platform? ";
    size_t target_number{};
    std::cin >> target_number;
    auto target = targets.find(target_number)->second;

    std::cout << "\nbuild mode (debug ---> 1, release ---> 2)? ";
    size_t build_mode{};
    std::cin >> build_mode;

    std::cout << "\nbuild type (executable ---> 1, shared (dynamic) library ---> 2)? ";
    size_t build_type{};
    std::cin >> build_type;

    std::cout << "\noutput filename? ";
    std::string output_filename{};
    std::cin >> output_filename;

    try
    {
        auto zig_command = std::string{ "zig c++ -std=c++23 " };
        zig_command += project_root_path;
        zig_command += std::string{ "/src/*.cpp -I " };
        zig_command += project_root_path;
        zig_command += std::string{ "/include -target " };

        auto debug_command = std::string{ " -g " };
        auto shared_library_command = std::string{ " -shared " };

        auto win_exe_output_command = std::string{ " -o " } + project_root_path + std::string{ "/build/" } + output_filename + std::string{ ".exe " };
        auto win_shared_output_command = std::string{ " -o " } + project_root_path + std::string{ "/build/" } + output_filename + std::string{ ".dll " };
                
        auto non_win_exe_output_command = std::string{ " -o " } + project_root_path + std::string{ "/build/" } + output_filename;
        auto linux_shared_output_command = std::string{ " -o " } + project_root_path + std::string{ "/build/lib" } + output_filename + std::string{ ".so " };
        auto darwin_shared_output_command = std::string{ " -o " } + project_root_path + std::string{ "/build/lib" } + output_filename + std::string{ ".dylib " };
        
        auto release_mode_flag_fast = std::string{ " -Doptimize=ReleaseFast " };
        auto release_mode_flag_safe = std::string{ " -Doptimize=ReleaseSafe " };
        auto release_mode_flag_small= std::string{ " -Doptimize=ReleaseSmall " };

        switch (build_mode)
        {
        case 1:// debug
            switch (build_type)
            {
            case 1:// executable
                [&]()
                {
                    /*
                    zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-unknown-linux-gnu -g -o build/output
                    zig c++ -std=c++23 src/*.cpp -I ./include -target armv7-unknown-linux-gnueabihf -g -o build/output
                    zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-unknown-linux-musl -g -o build/output
                    zig c++ -std=c++23 src/*.cpp -I ./include -target arm64-unknown-linux-gnu -g -o build/output
                    zig c++ -std=c++23 src/*.cpp -I ./include -target aarch64-apple-darwin -g -o build/output
                    zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-apple-darwin -g -o build/output
                    zig c++ -std=c++23 src/*.cpp -I ./include -target i686-pc-windows-msvc -g -o build/output.exe
                    zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-pc-windows-msvc -g -o build/output.exe
                    */
                    auto command = zig_command + target + debug_command;
                    switch (target_number)
                    {
                    case 7:
                        command += win_exe_output_command;
                        break;
                    case 8:
                        command += win_exe_output_command;
                        break;
                    default:
                        command += non_win_exe_output_command;
                        break;
                    }
                    std::cout << '\n' << command << std::endl;
                }();
                break;
            case 2:// shared (dynamic) library
                [&]()
                {
                    /*
                    zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-unknown-linux-gnu -g -shared -o build/liboutput.so
                    zig c++ -std=c++23 src/*.cpp -I ./include -target armv7-unknown-linux-gnueabihf -g -shared -o build/liboutput.so
                    zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-unknown-linux-musl -g -shared -o build/liboutput.so
                    zig c++ -std=c++23 src/*.cpp -I ./include -target arm64-unknown-linux-gnu -g -shared -o build/liboutput.so
                    zig c++ -std=c++23 src/*.cpp -I ./include -target aarch64-apple-darwin -g -shared -o build/liboutput.dylib
                    zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-apple-darwin -g -shared -o build/liboutput.dylib
                    zig c++ -std=c++23 src/*.cpp -I ./include -target i686-pc-windows-msvc -g -shared -o build/output.dll
                    zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-pc-windows-msvc -g -shared -o build/output.dll
                    */
                    auto command = zig_command + target + debug_command + shared_library_command;
                    switch (target_number)
                    {
                    case 1:
                        command += linux_shared_output_command;
                        break;
                    case 2:
                        command += linux_shared_output_command;
                        break;
                    case 3:
                        command += linux_shared_output_command;
                        break;
                    case 4:
                        command += linux_shared_output_command;
                        break;
                    case 5:
                        command += darwin_shared_output_command;
                        break;
                    case 6:
                        command += darwin_shared_output_command;
                        break;
                    case 7:
                        command += win_shared_output_command;
                        break;
                    case 8:
                        command += win_shared_output_command;
                        break;
                    default:
                        break;
                    }
                    std::cout << '\n' << command << std::endl;
                }();
                break;
            default:
                throw std::runtime_error("Invalid build type ('executable' or 'shared') in debug mode.");
                break;
            }  
            break;
        case 2:// release
            [&]()
            {
                std::cout  << "\nrelease mode optimization flag (fast ---> 1, safe ---> 2, small ---> 3)? ";
                size_t release_mode_optimization_flag_number{};
                std::cin >> release_mode_optimization_flag_number;                
                switch (build_type)
                {
                case 1:// executable
                    [&]()
                    {
                        /*
                        zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-unknown-linux-gnu -Doptimize=ReleaseFast -o build/output
                        zig c++ -std=c++23 src/*.cpp -I ./include -target armv7-unknown-linux-gnueabihf -Doptimize=ReleaseFast -o build/output
                        zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-unknown-linux-musl -Doptimize=ReleaseFast -o build/output
                        zig c++ -std=c++23 src/*.cpp -I ./include -target arm64-unknown-linux-gnu -Doptimize=ReleaseFast -o build/output
                        zig c++ -std=c++23 src/*.cpp -I ./include -target aarch64-apple-darwin -Doptimize=ReleaseFast -o build/output
                        zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-apple-darwin -Doptimize=ReleaseFast -o build/output
                        zig c++ -std=c++23 src/*.cpp -I ./include -target i686-pc-windows-msvc -Doptimize=ReleaseFast -o build/output.exe
                        zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-pc-windows-msvc -Doptimize=ReleaseFast -o build/output.exe
                        */
                        auto command = zig_command + target;
                        switch (release_mode_optimization_flag_number)
                        {
                        case 1:// fast
                            command += release_mode_flag_fast;
                            break;
                        case 2:// safe
                            command += release_mode_flag_safe;
                            break;
                        case 3:// small
                            command += release_mode_flag_small;
                            break;
                        default:
                            throw std::runtime_error("Invalid release mode optimization flag ('fast' or 'safe' or 'small') in release mode, executable output type.");
                            break;
                        }
                        switch (target_number)
                        {
                        case 7:
                            command += win_exe_output_command;
                            break;
                        case 8:
                            command += win_exe_output_command;
                            break;
                        default:
                            command += non_win_exe_output_command;
                            break;
                        }
                        std::cout << '\n' << command << std::endl;
                    }();
                    break;
                case 2:// shared (dynamic) library
                    [&]()
                    {
                        /*
                        zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-unknown-linux-gnu -Doptimize=ReleaseFast -o build/liboutput.so
                        zig c++ -std=c++23 src/*.cpp -I ./include -target armv7-unknown-linux-gnueabihf -Doptimize=ReleaseFast -o build/liboutput.so
                        zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-unknown-linux-musl -Doptimize=ReleaseFast -o build/liboutput.so
                        zig c++ -std=c++23 src/*.cpp -I ./include -target arm64-unknown-linux-gnu -Doptimize=ReleaseFast -o build/liboutput.so
                        zig c++ -std=c++23 src/*.cpp -I ./include -target aarch64-apple-darwin -Doptimize=ReleaseFast -o build/liboutput.dylib
                        zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-apple-darwin -Doptimize=ReleaseFast -o build/liboutput.dylib
                        zig c++ -std=c++23 src/*.cpp -I ./include -target i686-pc-windows-msvc -Doptimize=ReleaseFast -o build/output.dll
                        zig c++ -std=c++23 src/*.cpp -I ./include -target x86_64-pc-windows-msvc -Doptimize=ReleaseFast -o build/output.dll
                        */
                        auto command = zig_command + target;
                        switch (release_mode_optimization_flag_number)
                        {
                        case 1:// fast
                            command += release_mode_flag_fast;
                            break;
                        case 2:// safe
                            command += release_mode_flag_safe;
                            break;
                        case 3:// small
                            command += release_mode_flag_small;
                            break;
                        default:
                            throw std::runtime_error("Invalid release mode optimization flag ('fast' or 'safe' or 'small') in release mode, shared (dynamic) library output type.");
                            break;
                        }
                        switch (target_number)
                        {
                        case 1:
                            command += linux_shared_output_command;
                            break;
                        case 2:
                            command += linux_shared_output_command;
                            break;
                        case 3:
                            command += linux_shared_output_command;
                            break;
                        case 4:
                            command += linux_shared_output_command;
                            break;
                        case 5:
                            command += darwin_shared_output_command;
                            break;
                        case 6:
                            command += darwin_shared_output_command;
                            break;
                        case 7:
                            command += win_shared_output_command;
                            break;
                        case 8:
                            command += win_shared_output_command;
                            break;
                        default:
                            break;
                        }
                        std::cout << '\n' << command << std::endl;
                    }();
                    break;
                default:
                    throw std::runtime_error("Invalid build type ('executable' or 'shared (dynamic) library') in release mode.");
                    break;
                }                
            }();
            break;
        default:
            throw std::runtime_error("Invalid build mode ('debug' or 'release').");
            break;
        }

        return 0;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
}
