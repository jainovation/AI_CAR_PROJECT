시나리오
=======
1. 운영

	가. 기본 시나리오

		- 차량 전원 인가 후 프로그램 실행 후 출발

		- IMU 로 속도 측정

		- 속도제어


	나. 차선유지 시스템 시나리오

		- 카메라로 영상 획득  

		- OpenCV 차선 인식 후 차선을 따라 운행.

		- 코너 차선에서 조향각 조절


	다. 사물 인식 시나리오

		- 카메라로 영상 획득, Yolo를 활용한 물체 Detection

		- 차량, 신호등, 보행차 및 장애물 인식

		- 신호에 따른 출발/정지 및 장애물 감지 시 차량 정지


	라. 거리유지 시스템(ACC) 시나리오
 
		- 카메라로 차량 인식 후

		- Lidar를 사용하여 앞 차와 거리유지 

		- 거리 유지를 위해 가속/감속


	마. 자동주차 시나리오 (가능할 시)

		- 초음파 센서로 주변 장애물 거리 측정

		- 자동주차