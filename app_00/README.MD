# Урок 1
> Подключаем daScript к c++ проекту

## Введние

В этом уроке мы научимся подключать библиотеку daScript к С++ проекту и запускать das скрипты.

## Подготовка

Чтобы пропустить часть не касающуюся daScript я создал специальный базовый проект. Все что он содержит это библиотеку daScript, а так же базовые настройки cmake. Скачать и собрать его можно следующим образом:

```bash
git clone https://github.com/reOiL/das_lesson
cd das_lesson
git checkout base_template
git submodule update --init --recursive
mkdir build
cd build
cmake ..
cmake --build .
```

## Основная часть

Для начала создадим папку app_00 в папке базового проекта.
Затем внутри это папки создаем `CMakeLists.txt` со следующим содержанием:

```cmake
# Название проекта
project(app_00)

# Компилирем проект
add_executable(${PROJECT_NAME} main.cpp)

# Линкуем проект с бибилиотекой daScript, она нужна для выполнения das скриптов
target_link_libraries(${PROJECT_NAME} libDaScript)

# Меняем папку выходного файла на текущую
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
```

Теперь давайте создадим папку script, которая будет содержать все наши скрипты, а затем создадим в ней файл с именем `main.das` и напишем в нем наш первый скрипт:

```python
// Аннотация init означает что функция является точкой входа в программу
[init]
def main()
    print("Hello daScript!")
```

Далее нам потребуется создать файл main.cpp, который и будет исполнять наш das файл.

Для начала подключим заголовочный файл daScript.h

```c++
#include "daScript/daScript.h"

// разрешаем использовать пространство имен без идентификатора
using namespace das;
```

Затем в функции `main` нам необходимо подключить и инициализировать основной модуль daScript `$`, он содержит все основные типы и функции:

```c++
int main()
{
    NEED_MODULE(Module_BuiltIn)
    Module::Initialize();
```

Чтобы запустить das скрипт нам необходимо скомпилировать и выполнить его. Для компиляции нам потребуется следующий код:

```c++
    TextPrinter tout;
    ModuleGroup dummyLibGroup;
    // создаем файловую систему daScript, обратите внимание что вы можете создать свою файловую систему при необходимости
    auto fAccess = make_smart<FsFileAccess>();
    auto program = compileDaScript("script/main.das", fAccess, tout, dummyLibGroup); // компилируем на dascript файл
    if ( program->failed() ) // если компиляция не успешна выводим ошибку и выходим
    {
        tout << "failed to compile\n";
        for ( auto & err : program->errors )
            tout << reportError(err.at, err.what, err.extra, err.fixme, err.cerr );
        return -1;
    }
```

Для исполнения:

```c++
    Context ctx(program->getContextStackSize()); // Создаем новый контекст это что-то вроде подпрограммы содержаший стэк и выполняющий наш скрипт
    if ( !program->simulate(ctx, tout) ) { // выполняем наш скрипт и в случае ошибки выводим её на экран.
        tout << "failed to simulate\n";
        for ( auto & err : program->errors )
            tout << reportError(err.at, err.what, err.extra, err.fixme, err.cerr );
        return -1;
    }
```

В конце необходимо отключить daScript модули

```c++
    Module::Shutdown();
}
```

[Полный C++ код](https://github.com/reOiL/das_lesson/tree/master/app_00/main.cpp)

## Заключение

Сегодня мы научились подключать daScript к С++ проекту.
