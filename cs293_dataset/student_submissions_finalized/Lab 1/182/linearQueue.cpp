template <typename T> bool DynamicQueue <T>:: isEmpty()
{
  return (head-tail==0);
}
template <typename T> unsigned int DynamicQueue  <T>:: size()
{
  return tail - head;
}
template <typename T> bool DynamicQueue <T>:: isFull()
{
  return (size()==N);
}
template <typename T> void DynamicQueue  <T>::grow()
{ 
  T *large;
  N = nextSize();
  large=new T[N];
  for(int i=0;i<size();i++)
  {large[i]=A[i];};
  A=large;

}
template <typename T> void DynamicQueue  <T>::QInsert(T x)
{
  if(isFull()){
    grow();
  }
  if(head > 0  && tail == N ){
    for(int i=0;i<size();i++){
      A[i] = A[i+head];
    }
    tail=tail-head;
    head = 0;
  }
A[tail]=x;
tail++;
}
template <typename T>  bool DynamicQueue  <T> ::QDelete(T *x)
{
  if (isEmpty())
    return false;
  else
    *x = A[head];
      head++;
  return true;
}