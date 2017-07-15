# Contributing
OpenCK lives upon the contributions from the community. This is a quick guide for any person looking to help out, so all of us aren't confused about anything involved in the contributing process.

## 1) What a contribution should do
Every contribution should accomplish something, whether it be solving an issue or adding a new feature. Try to avoid changes that are so minor that they don't impact OpenCK positively whatsoever (things like the entire contribution is just fixing one minor typo in a debug message).

That being said, there is a time and a place for fixing very minor issues, and the fixes should be included along with more impactful changes to avoid overwhelming the maintainers with the amount of changes they have to review.

## 2) Setting up
As the README says, OpenCK is made using C++/Qt. Qt Creator should be installed from [here](https://info.qt.io/download-qt-for-application-development). If you have Qt Creator already installed, the version should be 5.8+.
We use MSVC2015 for compiling code, and the choice of debugger is yours, albeit the vast majority of the team uses WinDbg.

Afterwards, just run `git clone` or use Qt's built in Git Tools via Tools->Git from the menu.

## 3) Code style
Maintaining consistency in the code is important for readability. Here is what we use:

### 3.1) Brace placements
In OpenCK, we use a modified K&R style, so if something is not specifically mentioned, use K&R style.
This means functions have a new line before the brace.
```cpp
int main(int argc, char* argv[])
{
  //good
}

int main(int argc, char* argv[]) {
  //bad
}
```

Inside functions, control flow (if, for, while etc.) statements are One True Brace, meaning the brace should both never be omitted and be on the same line as the statement.
```cpp
if (someBoolFunction()) {
    doSomething(); //good
}

if (someOtherBoolFunction())
{
    doSomethingElse(); //bad
}

if (anotherBoolFunction())
    doSomethingIfTrue(); //bad
doSomethingAlways();
```
Class and namespaces should have brackets on a newline like functions.
```cpp
namespace ANamespace
{
    class SomeClass;
}

class SomeClass
{
public:
    void aFunctionProto();
};
```

### 3.2) Indents
Indents are 4 spaces, and should be used every new codeblock. It should be noted that nesting any more than 3 blocks inside a function is probably a sign you should re-write that section of your program to be less nested.
```cpp
void someFunction(SomeClass* ptr)
{
    if (ptr->someBoolFunction()) {
        for(int i = 0; i < ptr->someIntFunction(); i++) {
            doSomething(i);
        }
    }
}
```
Switch statements should have case statements indented, and the code on a new line.
```cpp
switch (suffix) {
    case 'x':
        doSomething(); 
        break;
    case 'y':
        doSomethingElse();
        break;
    default:
        break;
}
```
### 3.3) Spacing
For control flow statements, a space should be between the statement and the brace, as well as the keyword of the statement (if) and the body of the statement (things between the parentheses).
```cpp
if (someBool()) {
    //good
}
if(someOtherBool()){
    //bad
}
```
Do NOT add spaces in between the parentheses and the parameter when calling a function
This is BAD:
```cpp
int i = someIntFunction( &variable );
```
Also, there should be no space after a pointers type and the asterisk denoting that it is a pointer.
```cpp
int* good;
int *bad;
```
### 3.4) Naming
Variables and classes should have a descriptive, not totally long name. A temporary variable for example, should be named temp or tmp, not ThisIsATemporaryVariableName.

Variable & Function name should be lowerCamelCase.
Class & Namespace names should be UpperCamelCase.

### 3.5) Commenting
Comments are important for readability, but one must avoid the trap of over commenting. If something in the code is too confusing, comment on what that specific part is doing.
Every function should have a Doxygen documentation comment above it. If you have used JavaDocs before, Doxygen is very similar.

```cpp
/**
* Some description of things
* @brief SomeClass::someFunction(int, double)
* @param i A description of the variable
* @param x Another variable description
* @return Some description of the return value
* @see SomeClass:anotherFunction(int, int)
*/
int SomeClass::someFunction(int i, double x)
{
....
}
```

### 3.6) UI
UI is a large part of the OpenCK, so it is rather obvious that people will want to contribute to said UI.

We use Qt Creator's forms (.ui files) for making UI, and then have qmake and the compiler do the code generation. 

The UI Designer exists. Use it when you can. There is no point in making something more complicated for yourself, making our codebase larger.

For Qt's slots system coordinating between .ui files and the code, a couple of things.

Push buttons should have an on_actionAction_Name_Here_triggered() slot, as they are pushed so there is no trigger on/off for them.

Checkboxes should have the triggered function as well, but with a bool parameter to signify whether it was checked on or off.

Radio buttons you might actually have to go into the code for a QActionGroup, but in most cases radio buttons are largely unnecssary.

## 4) Pull requests
For git, each pull request should have some info, so the maintainers can know some things beforehand.

What are the expected results of this change?

Is it tested?

If tested, did it work/achieve expected results?

What issues, if any, were fixed?

## 5) Debugging
So an error happened in your code, no worries, it happens to all of us. 

This section will help you fix this.

### 5.1) Common Errors & Solutions
LNK2019, unresolved external symbol.

Fix: Build->Clean All, Build->Run qmake, Recompile.

LNK2001, unresolved external symbol.

Fix: Try the fix for LNK2019, if not it may be caused by many reasons having to do with file scope.

Trying to access any static variables from outside of the file in which they are declared can result in a LNK2001.

Any other causes may be found [here](https://msdn.microsoft.com/en-us/library/f6xx1b1z.aspx).

I don't know whether or not my code worked because of no output!

Try doing a qDebug() call from <QDebug> to print your variables you want to know that will indicate success.
```cpp
qDebug() << "Variables are: " << variableOne << variableTwo;
```
If you use a debugger, placing a breakpoint after your code and then checking the variable list will also do this.

My code compiled but then crashed midway through!

This can be caused by many things. For one, read the crash message and see if anything it says makes any sense. This will help you pinpoint the error. It may also help to insert `qDebug()` messages after each step of your code, and see where the output stops to see specifically when the crash occured (before or after a specific message). Stepping through with the debugger also helps you pinpoint the error.

## 6) Where can I start?
Finding a place to start work is sometimes confusing for beginners, so a great place to find things to do is go onto the Discord for the OpenCK project, and ask around.

If you've read to the end, we're glad you are looking to help contribute, Happy Modding!