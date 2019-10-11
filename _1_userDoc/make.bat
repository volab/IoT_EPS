@ECHO OFF

pushd %~dp0

:: Command file for Sphinx documentation

if "%SPHINXBUILD%" == "" (
    set SPHINXBUILD=python -msphinx
)
set DOC_HOME=%cd%
set SOURCEDIR=source
set BUILDDIR= ..\..\webDoc
set SPHINXPROJ=IoT_EPS
set SOURCE_C_DIR=..\_3_software\IoT_EPS


if "%1" == "" goto help

cd %SOURCE_C_DIR%
REM dir
doxygen DoxyFile
cd %DOC_HOME%
echo %cd%
REM dir

goto end

%SPHINXBUILD% >NUL 2>NUL
if errorlevel 9009 (
    echo.
    echo.The Sphinx module was not found. Make sure you have Sphinx installed,
    echo.then set the SPHINXBUILD environment variable to point to the full
    echo.path of the 'sphinx-build' executable. Alternatively you may add the
    echo.Sphinx directory to PATH.
    echo.
    echo.If you don't have Sphinx installed, grab it from
    echo.http://sphinx-doc.org/
    exit /b 1
)

%SPHINXBUILD% -M %1 %SOURCEDIR% %BUILDDIR% %SPHINXOPTS%


:: recupération de la branch active dans la variable : "v_branch"
for /f %%i in ('git symbolic-ref HEAD --short') do set v_branch=%%i


if %v_branch% == master (
    echo.
    echo ************************************
    echo.
    echo branch : %v_branch%.
    echo Envoie de la doc vers gh-pages
    echo.
    echo ************************************
    echo.
    

    :: reconstruction de la branch "gh-pages" et mise a jour du depot distant
    cd %BUILDDIR%\html
    git add .
    git commit -m "rebuilt docs"
    git push origin gh-pages
    

    goto end
) else (
    echo.
    echo ************************************
    echo.
    echo Branch : %v_branch%
    echo La doc reste en local
    echo.
    echo ************************************
    echo.
    

    goto end
)

:end

popd
