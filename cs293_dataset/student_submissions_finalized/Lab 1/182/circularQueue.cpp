template <typename T> bool DynamicQueue <T>:: isEmpty()
{
  return (head-tail==0);
}
template <typename T> bool DynamicQueue <T>:: isFull()
{
  if (((tail == N - 1 )&&( head == 0))||(head-tail==1))
    return true;
  else 
    return false;
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
template <typename T> unsigned int DynamicQueue  <T>:: size()
{
  if(tail>=head)
    return tail - head;
  else
    return N+1-tail+head;
}
template <typename T> void DynamicQueue  <T>::QInsert(T x)
{
  if(isFull()){
    grow();
  }
  if(head > 0  && tail == N ){
    tail=0;
    A[tail]=x;
    return;
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