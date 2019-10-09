#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct list{ //�� randomRank �ϥΪ���C 
	int n;
	struct list *next;
};

void swap(int *a, int *b){//�洫��� 
	int t;
	t=*a;
	*a=*b;
	*b=t;
}

void selectSort(int *arr){ //selection sort�A�̫�^�Ǫ���ƭȬOswap�禡���ϥΦ��� 
	int i, j; //for �j��n�Ϊ� 
	int min; //�̤p�Ȫ����� 
	
	for(i=0;i<9999;i++){//�H�U�N�Oselection sort���D�{���A�o�̤��حz��z 
		min=i;
		for(j=i+1; j<10000; j++){
				if(arr[j] < arr[min]){
				min=j;
			}
		}	 
			swap(&arr[i], &arr[min]);
		}
	}

void negativeRank(int *arr){//��}�C�q10000�ƨ�1 
	int i;
	for(i=10000; i>=1; i--){
		arr[10000-i]=i;
	}
}

void postiveRank(int *arr){//��}�C�q1�ƨ�10000 
	int i;
	for(i=0; i<10000; i++){
		arr[i]=i+1;
	}
}

void randomRank(int *arr){
	struct list *temp=NULL, *first=NULL, *trave=NULL; //�ȮɥΫ��СB���V��C�Ĥ@�Ӥ��������СB�C���Ϋ��� 
	int i, j;
	
	srand((unsigned)time(NULL)); //�üƺؤl 
	
	for(i=10000;i>=1;i--){ //���ͱq1�ƨ�10000����C 
		first=(struct list*)malloc(sizeof(struct list));
		first->next=temp;
		first->n=i;
		temp=first;
	}

	for(i=10000;i>=1;i--){ //�q��C�̩�X��ơA��i�}�C�� 
		int n;
		n=rand();//�ü� 
		trave=first;//�q�Y�C�� 
		for(j=0;j<n%i;j++){//��trave���в����C���� n%i �����(i�N���C�j�p-1) 
			temp=trave;
			trave=trave->next;
		}
		arr[10000-i]=trave->n;//���쪺��Ʃ�i�}�C�� 
		if(trave==first){//���F�T�O�}�C�̪���Ƥ��|���СA�Q��쪺��C��ƭn�����A�o�̳B�z���O��C���Ĥ@����� 
			first=trave->next;//����trave�����`�I 
			free(trave);//����trave�����O����Ŷ� 
		}
		else{//�o�̳B�z���O���F��C�Ĥ@�Ӹ�ƥH�~���Ҧ���L��� 
			temp->next=trave->next;
			free(trave);
		}
	}
}

void duplicateCheck(int *arr){ //�ΨӽT�{�}�C�̪���ƬO�_������ 
	int r[10001]={0}; //��ΨӰO����r�}�C�������k�s 
	int i;
	for(i=0;i<10000;i++){//�ˬd�}�C���Ҧ���� 
		if(r[arr[i]]==0) r[arr[i]]=1; //r�}�C����arr[i]�ӬO0���ܡA�N��Ĥ@���J��arr[i]�C�{�b�J��F�A�ҥH�n��r�}�C����arr[i]�ӳ]��1�A��ܰ}�C�̤w��arr[i]���Ʀr�C 
		else{
			printf("yes\n");
			break;
		}
	}
	printf("no\n");
}

void printArr(int *arr){ //�Ψӿ�X�}�C��� 
	int i;
	for(i=0;i<10000; i++) printf("%d\n", arr[i]);
}

int main(){
	int i;
	int myArr[10000];
	double duration;//�Ψӭp�����100���ƧǡA�Ҫ�O���ɶ����`�X
	time_t start; // �O�� selectSort ��}�l���檺�ɶ� 
	
	duration=0;
	for(i=0;i<100;i++){//����100�� 
		postiveRank(myArr);//��Ƥw�Ƨ� 
		start=clock();//�}�l�p�� 
		selectSort(myArr); //�Ƨ�+�p������ 
		duration+=((double)(clock()-start))/CLOCKS_PER_SEC; //�O��selectSort���`����ɶ� 
	}
	printf("postiveRank �����ƧǮɶ���F%.4f��\n", duration/100);//��X�����ɶ�
	//�H�U������������ 114~112 ���{���X�A�u�O���p���P 
	duration=0;	
	for(i=0;i<100;i++){
		negativeRank(myArr);//��ưf�Ƨ� 
		start=clock();
		selectSort(myArr);
		duration+=((double)(clock()-start))/CLOCKS_PER_SEC;
	}
	printf("negativeRank �����ƧǮɶ���F%.4f��\n", duration/100); 
	
	duration=0;
	for(i=0;i<100;i++){
		randomRank(myArr);//����H���Ƨ� 
		start=clock();
		selectSort(myArr);
		duration+=((double)(clock()-start))/CLOCKS_PER_SEC;
	}
	printf("randomRank �����ƧǮɶ���F%.4f��\n", duration/100); 
	
	return 0;
}
