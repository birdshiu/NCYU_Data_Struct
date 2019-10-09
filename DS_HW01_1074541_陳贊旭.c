#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct list{ //給 randomRank 使用的串列 
	int n;
	struct list *next;
};

void swap(int *a, int *b){//交換兩數 
	int t;
	t=*a;
	*a=*b;
	*b=t;
}

void selectSort(int *arr){ //selection sort，最後回傳的整數值是swap函式的使用次數 
	int i, j; //for 迴圈要用的 
	int min; //最小值的索引 
	
	for(i=0;i<9999;i++){//以下就是selection sort的主程式，這裡不贅述原理 
		min=i;
		for(j=i+1; j<10000; j++){
				if(arr[j] < arr[min]){
				min=j;
			}
		}	 
			swap(&arr[i], &arr[min]);
		}
	}

void negativeRank(int *arr){//把陣列從10000排到1 
	int i;
	for(i=10000; i>=1; i--){
		arr[10000-i]=i;
	}
}

void postiveRank(int *arr){//把陣列從1排到10000 
	int i;
	for(i=0; i<10000; i++){
		arr[i]=i+1;
	}
}

void randomRank(int *arr){
	struct list *temp=NULL, *first=NULL, *trave=NULL; //暫時用指標、指向串列第一個元素的指標、遊歷用指標 
	int i, j;
	
	srand((unsigned)time(NULL)); //亂數種子 
	
	for(i=10000;i>=1;i--){ //產生從1排到10000的串列 
		first=(struct list*)malloc(sizeof(struct list));
		first->next=temp;
		first->n=i;
		temp=first;
	}

	for(i=10000;i>=1;i--){ //從串列裡抽出資料，放進陣列裡 
		int n;
		n=rand();//亂數 
		trave=first;//從頭遊歷 
		for(j=0;j<n%i;j++){//把trave指標移到串列的第 n%i 筆資料(i代表串列大小-1) 
			temp=trave;
			trave=trave->next;
		}
		arr[10000-i]=trave->n;//把抽到的資料放進陣列裡 
		if(trave==first){//為了確保陣列裡的資料不會重覆，被抽到的串列資料要移除，這裡處理的是串列的第一筆資料 
			first=trave->next;//忽略trave指的節點 
			free(trave);//釋放trave指的記憶體空間 
		}
		else{//這裡處理的是除了串列第一個資料以外的所有其他資料 
			temp->next=trave->next;
			free(trave);
		}
	}
}

void duplicateCheck(int *arr){ //用來確認陣列裡的資料是否有重覆 
	int r[10001]={0}; //把用來記錄的r陣列先全都歸零 
	int i;
	for(i=0;i<10000;i++){//檢查陣列的所有資料 
		if(r[arr[i]]==0) r[arr[i]]=1; //r陣列的第arr[i]個是0的話，代表第一次遇到arr[i]。現在遇到了，所以要把r陣列的第arr[i]個設成1，表示陣列裡已有arr[i]的數字。 
		else{
			printf("yes\n");
			break;
		}
	}
	printf("no\n");
}

void printArr(int *arr){ //用來輸出陣列資料 
	int i;
	for(i=0;i<10000; i++) printf("%d\n", arr[i]);
}

int main(){
	int i;
	int myArr[10000];
	double duration;//用來計算執行100次排序，所花費的時間的總合
	time_t start; // 記錄 selectSort 剛開始執行的時間 
	
	duration=0;
	for(i=0;i<100;i++){//執行100次 
		postiveRank(myArr);//資料已排序 
		start=clock();//開始計時 
		selectSort(myArr); //排序+計錄次數 
		duration+=((double)(clock()-start))/CLOCKS_PER_SEC; //記錄selectSort的總執行時間 
	}
	printf("postiveRank 平均排序時間花了%.4f秒\n", duration/100);//輸出平均時間
	//以下的部份都類似 114~112 的程式碼，只是情況不同 
	duration=0;	
	for(i=0;i<100;i++){
		negativeRank(myArr);//資料逆排序 
		start=clock();
		selectSort(myArr);
		duration+=((double)(clock()-start))/CLOCKS_PER_SEC;
	}
	printf("negativeRank 平均排序時間花了%.4f秒\n", duration/100); 
	
	duration=0;
	for(i=0;i<100;i++){
		randomRank(myArr);//資料隨機排序 
		start=clock();
		selectSort(myArr);
		duration+=((double)(clock()-start))/CLOCKS_PER_SEC;
	}
	printf("randomRank 平均排序時間花了%.4f秒\n", duration/100); 
	
	return 0;
}
