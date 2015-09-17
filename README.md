# sorting_algorithms
compare each sorting algorithms

정렬을 담당하는 Sort클래스를 별도로 정의.
Sort의 정적 멤버 함수 BubbleSort, QuickSort, RadixSort, ExternalMergeSort가 정렬을 수행
템플릿을 통한 범용 정렬 클래스를 만들었으나 RadixSort와 ExternalMergeSort는 int형 정렬에 대해서만 구현.
RadixSort는 최대 지수 32, 기수 2로 설정. 매개변수 변경을 통해 정렬 기준 변경 가능
ExternalSort는 입력 파일을 원소가 1024(BUFFER_SIZE로 정의됨)개인 임시 파일로 분할한 후 이를 둘씩 묶어 병합 정렬을 수행.
수행시간은 command line에서 입력한 출력파일에 같이 출력, ExternalSort의 결과는 [출력파일].result로 출력.
두 자료간의 비교는 compare함수를 이용. 여기서는 임의로 intAscending함수를 이용해 오름차순 정렬을 수행
