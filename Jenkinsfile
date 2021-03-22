pipeline {
    agent any

    stages {
		stage('PreSetup') {
			steps {
				echo 'PreSetup..'
				sh 'git submodule update --init --recursive'
			}
		}
        stage('Build') {
            steps {
                echo 'Building..'
				sh script:'''
                    #!/bin/bash
				    cmake -S . -B build -G 'Visual Studio 16 2019' -DWarningsAsErrors:BOOL=ON
				    cd build
				    cmake --build .
				'''
				
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