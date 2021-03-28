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
		        cmake -S . -B build -G "Visual Studio 16 2019" -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DWarningsAsErrors:BOOL=ON
		        cd build
		        cmake --build .
		    '''
	   }
	}
       stage('Test') {
            steps {
                echo 'Testing..'
		        sh 'cppcheck src/ --enable=warning,style,performance,portability --inconclusive --error-exitcode=1'
		        sh 'cppcheck lib/Physics/src --enable=warning,style,performance,portability --inconclusive --error-exitcode=1'
		        sh script:'''
                    #!/bin/bash
		            cd ${WORKSPACE}/build/tests/Debug
		            ./tests.exe
		        '''
            }
        }
        stage('Deploy') {
            steps {
                echo 'Deploying....'
            }
        }
    }
    post {
        success {
            sh 'chmod 755 .jenkins/send.sh'
            sh '.jenkins/send.sh success $WEBHOOK_URL'
        }
        failure {
            sh 'chmod 755 .jenkins/send.sh'
            sh '.jenkins/send.sh failure $WEBHOOK_URL'
        }
        aborted {
            sh 'chmod 755 .jenkins/send.sh'
            sh '.jenkins/send.sh failure $WEBHOOK_URL'
        }
    }
}
