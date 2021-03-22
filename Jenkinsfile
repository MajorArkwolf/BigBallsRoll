pipeline {
    agent any

    stages {
		stage('PreSetup') {
			steps {
				echo 'PreSetup..'
				sh 'git lfs pull'
			}
		}
        stage('Build') {
            steps {
                echo 'Building..'
				sh 'mkdir -p build'
				sh 'cd build'
				sh 'cmake -S "../" -G "Visual Studio 15 2017" -DCMAKE_DISABLE_FIND_PACKAGE_WindowsSDK=ON -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DWarningsAsErrors:BOOL=ON -D CMAKE_GENERATOR_PLATFORM=x64'
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