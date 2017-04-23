#include<iostream> 
using namespace std;
#define big 10007
#define test 8
char ti[51];//题干 
int size;//选项个数
int result[test];//准备试的数
bool prior(char a, char b){//运算符a优先级是否大于b
	if (a == '^')return true;
	if (b == '^')return false;
	if (a == '*')return true;
	if (b == '*')return false;
	return true;
}
int power(int a, int b){//乘幂函数要取余
	int i;
	int ans = 1;
	for (i = 0; i < b; i++){
		ans *= a;
		ans %= big;
	}
	return ans;
}
int op(int a, int b, char o){
	switch (o){
	case '^':return power(a, b);
	case '*':a *= b; a %= big; return a;
	case '+':return (a + b) % big;
	case '-':return (a - b) % big;
	}
}
//x表示数字，o表示符号
int calculate(int x[], int xsize, char o[], int osize){
	int i;
	int xstack[51];
	int xtop = 0;
	char ostack[51];
	int otop = 0;
	int xi, oi;
	xi = oi = 0;
	xstack[xtop++] = x[xi++];
	while (xi<xsize&&oi<osize){
		while (otop != 0 && prior(ostack[otop - 1], o[oi])){
			xstack[xtop - 2] = op(xstack[xtop - 2], xstack[xtop - 1], ostack[otop - 1]);
			xtop--;
			otop--;
		}
		ostack[otop++] = o[oi++];
		xstack[xtop++] = x[xi++];
	}
	while (otop >0){
		xstack[xtop - 2] = op(xstack[xtop - 2], xstack[xtop - 1], ostack[otop - 1]);
		xtop--;
		otop--;
	}
	return xstack[0];
}
int go(char ex[], int a){
	int i, j;
	int x[51];
	int xi = 0;
	char o[51];
	int oi = 0;
	i = 0;
	while (ex[i]){
		while (ex[i] == ' ')i++;
		if (ex[i] == 0)break;
		if (ex[i] == '('){
			int left = 1;
			char temp[51];
			j = 0;
			i++;
			while (true){
				temp[j] = ex[i];
				if (temp[j] == '(')left++;
				else if (temp[j] == ')')left--;
				if (left == 0){
					temp[j] = 0;
					x[xi++] = go(temp, a);
					i++;
					break;
				}
				i++; j++; 
			}
		}
		else if (ex[i] == 'a'){
			x[xi++] = a;
			i++;
		}
		else{
			int n = 0;
			while (ex[i] >= '0'&&ex[i] <= '9'){
				n *= 10;
				n += ex[i] - '0';
				i++;
			}
			x[xi++] = n;
		}
		while (ex[i] == ' ')i++;
		if (ex[i] == 0)break;
		if (ex[i] == '+' || ex[i] == '-' || ex[i] == '*' || ex[i] == '^'){
			o[oi++] = ex[i];
		} 
		i++;
	}
	return calculate(x, xi, o, oi);
}
int main()
{
	cin.getline(ti, sizeof(ti));
	cin >> size; 
	int i; 
	for (i = 0; i < test; i++)
	{
		result[i] = go(ti, i); 
	} 
	char choose[51],ch[27]="";
	int x=0;
	cin.getline(choose, 55);
	for (i = 0; i < size; i++){
		cin.getline(choose, 55);
		int j;
		int ans; 
		for (j = 0; j < test; j++){
			ans = go(choose, j); 
			if (ans != result[j])break;
		}
		if (j == test){
			ch[x++]=(char)(i + 'A');
		} 
	}
	printf("%s",ch);
	return 0;
}
