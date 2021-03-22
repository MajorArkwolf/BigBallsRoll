pipeline {
    agent any

    stages {
		stage('PreSetup') {
			steps {
				echo 'PreSetup..'
			}
		}
        stage('Build') {
            steps {
                echo 'Building..'
				sh script:'''
                    #!/bin/bash
				    cmake -S . -G "Visual Studio 16 2019" -DCMAKE_DISABLE_FIND_PACKAGE_WindowsSDK=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DWarningsAsErrors:BOOL=ON -D CMAKE_GENERATOR_PLATFORM=x64
				    cd build
				    cmake --build .
				
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
				sh 'build/BigBalls.exe --test'
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
}