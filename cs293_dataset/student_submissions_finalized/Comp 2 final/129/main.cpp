#include "main.h"

int main(int argc, char *argv[])
{
  int n;
  cin >> n;
  int last_index = 0;
  bool checksource[n];
  for (int i = 0; i < n; i++)
  {
    checksource[i] = true;
  }
  Node graph_nodes[n];
  for (int i = 0; i < n; i++)
  {
    graph_nodes[i].value = i + 1;
  }
  while (true)
  {
    int i, j;
    cin >> i >> j;
    if (i == -1 && j == -1)
    {
      break;
    }
    else
    {

      checksource[j - 1] = false;
      if (graph_nodes[i - 1].adjacenthead == nullptr)
      {
        graph_nodes[i - 1].adjacenthead = new listOfObjects<int>(j - 1);
        graph_nodes[i - 1].adjacenttail = graph_nodes[i - 1].adjacenthead;
      }
      else
      {
        graph_nodes[i - 1].adjacenttail->next = new listOfObjects<int>(j - 1);
        graph_nodes[i - 1].adjacenttail = graph_nodes[i - 1].adjacenttail->next;
      }
      if (graph_nodes[j - 1].secondadjacenthead == nullptr)
      {
        graph_nodes[j - 1].secondadjacenthead = new listOfObjects<int>(i - 1);
        graph_nodes[j - 1].secondadjacenttail = graph_nodes[j - 1].secondadjacenthead;
        graph_nodes[j - 1].from_counter++;
      }
      else
      {
        graph_nodes[j - 1].secondadjacenttail->next = new listOfObjects<int>(i - 1);
        graph_nodes[j - 1].secondadjacenttail = graph_nodes[j - 1].secondadjacenttail->next;
        graph_nodes[j - 1].from_counter++;
      }
    }
  }
  ofstream file("f.txt");

  file << "Source nodes: ";
  for (int i = 0; i < n; i++)
  {

    if (checksource[i])
    {
      file << i + 1 << " ";
    }
  }
  file << endl;
  similarity *head = nullptr;
  similarity *tail = nullptr;

  similarity *sourcehead = nullptr;
  similarity *sourcetail = nullptr;
  bool is_similar[n][n];
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      is_similar[i][j] = false;
    }
  }
  while (true)
  {
    int i, j;
    cin >> i >> j;
    if (i == -1 && j == -1)
    {
      break;
    }
    else
    {
      is_similar[i - 1][j - 1] = true;
      if (head == nullptr)
      {
        head = new similarity(i - 1, j - 1);
        tail = head;

        sourcehead = new similarity(i - 1, j - 1);
        sourcetail = sourcehead;
      }
      else
      {
        tail->next = new similarity(i - 1, j - 1);
        tail = tail->next;
        sourcetail->next = new similarity(i - 1, j - 1);
        sourcetail = sourcetail->next;
      }
    }
  }
  for (int i = 0; i < n; i++)
  {
    if (graph_nodes[i].from_counter == 1)
    {
      int x = graph_nodes[i].secondadjacenthead->object;
      tail->next = new similarity(i, x);
      is_similar[i][x] = true;
      tail = tail->next;
    }
  }
  similarity *garb1 = sourcehead;
  while (garb1 != nullptr)
  {
    // if(checksimilarity(garb1->b , garb1->a , sourcehead)){
    int keep_track = 0;
    if (garb1->a == garb1->b)
    {
      keep_track++;
    }

    Queue_BFS *queue1_head = new Queue_BFS(garb1->a, 0);
    Queue_BFS *queue2_head = new Queue_BFS(garb1->b, 0);
    Queue_BFS *queue1_tail = queue1_head;
    Queue_BFS *queue2_tail = queue2_head;
    int level1 = 0;
    level *maintain_level1head = new level(garb1->a, 0);
    ;
    level *maintain_level2head = new level(garb1->b, 0);
    level *maintain_level1tail = maintain_level1head;
    level *maintain_level2tail = maintain_level2head;
    int c = 1;
    while (queue1_head != nullptr && queue2_head != nullptr)
    {

      listOfObjects<int> *x = graph_nodes[queue1_head->x].adjacenthead;
      while (x != nullptr)
      {
        maintain_level1tail->next = new level(x->object, queue1_head->level + 1);
        queue1_tail->next = new Queue_BFS(x->object, queue1_head->level + 1);
        maintain_level1tail = maintain_level1tail->next;
        queue1_tail = queue1_tail->next;
        x = x->next;
      }
      x = graph_nodes[queue2_head->x].adjacenthead;
      while (x != nullptr)
      {
        maintain_level2tail->next = new level(x->object, queue2_head->level + 1);
        queue2_tail->next = new Queue_BFS(x->object, queue2_head->level + 1);
        maintain_level2tail = maintain_level2tail->next;
        queue2_tail = queue2_tail->next;
        x = x->next;
      }
      queue1_head = queue1_head->next;
      queue2_head = queue2_head->next;
    }

    level *x = maintain_level1head;
    while (x != nullptr)
    {
      if (x->level1 == 0)
      {
        x = x->next;
        continue;
      }
      level *y = maintain_level2head;
      while (y != nullptr)
      {
        if (y->level1 == 0)
        {
          y = y->next;
          continue;
        }

        listOfObjects<int> *garbage = graph_nodes[x->index].secondadjacenthead;

        bool t1 = true;
        bool t2 = true;
        while (garbage != nullptr)
        {
          bool isin1 = false;
          listOfObjects<int> *garbage2 = graph_nodes[y->index].secondadjacenthead;
          while (garbage2 != nullptr)
          {
            if (is_similar[garbage->object][garbage2->object])
            {
              isin1 = true;
              break;
            }
            garbage2 = garbage2->next;
          }
          if (!isin1)
          {
            t1 = false;
            break;
          }
          garbage = garbage->next;
        }
        listOfObjects<int> *garbage3 = graph_nodes[y->index].secondadjacenthead;
        while (garbage3 != nullptr)
        {
          bool isin1 = false;
          listOfObjects<int> *garbage2 = graph_nodes[x->index].secondadjacenthead;
          while (garbage2 != nullptr)
          {
            if (is_similar[garbage3->object][garbage2->object])
            {
              isin1 = true;
              break;
            }
            garbage2 = garbage2->next;
          }
          if (!isin1)
          {
            t2 = false;
            break;
          }
          garbage3 = garbage3->next;
        }
        if (t1 && t2)
        {
          if (!is_similar[x->index][y->index])
          {
            is_similar[x->index][y->index] = true;
            tail->next = new similarity(x->index, y->index);
            tail = tail->next;
          }
          if (!is_similar[y->index][x->index])
          {
            is_similar[y->index][x->index] = true;
            tail->next = new similarity(y->index, x->index);
            tail = tail->next;
          }
        }

        y = y->next;
      }
      x = x->next;
    }

    // }
    garb1 = garb1->next;
  }

  similarity *garb = head;
  file << "Similar node pairs: ";

  // while (garb != nullptr)
  // {
  //   /* code */
  //   file << "(" << garb->a + 1 << ", " << garb->b + 1 << ") ";
  //   garb = garb->next;
  // }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (is_similar[i][j])
      {
        file << "(" << i + 1 << ", " << j + 1 << ") ";
      }
    }
  }
  int a1[n][n + 1];

  similarity *xhead = head;
  int visited[n];
  for (int i = 0; i < n; i++)
  {
    visited[i] = 0;
  }
  listOfObjects<listOfObjects<int> *> *compressedmap = nullptr;
  listOfObjects<listOfObjects<int> *> *compressedmaptail = nullptr;

  int c = 0;
  // similarity *y1 = head;
  // while(y1!=nullptr){
  //   file<<y1->a<<" "<<y1->b<<endl;
  //   y1 = y1->next;
  // }

  while (c < n)
  {
    if (visited[c] == 0)
    {
      visited[c] = 1;
      if (compressedmap == nullptr)
      {
        listOfObjects<int> *yhead = new listOfObjects<int>(c);
        listOfObjects<int> *ytail = yhead;

        Queue_BFS *head_BFS = new Queue_BFS(c, 0);
        Queue_BFS *tail_BFS = head_BFS;
        while (head_BFS != nullptr)
        {
          similarity *y1 = head;
          while (y1 != nullptr)
          {
            if (y1->a == head_BFS->x)
            {
              if (visited[y1->b] == 0)
              {
                visited[y1->b] = 1;
                tail_BFS->next = new Queue_BFS(y1->b, 0);
                tail_BFS = tail_BFS->next;
                ytail->next = new listOfObjects<int>(y1->b);
                ytail = ytail->next;
              }
            }
            if (y1->b == head_BFS->x)
            {
              if (visited[y1->a] == 0)
              {
                visited[y1->a] = 1;
                tail_BFS->next = new Queue_BFS(y1->a, 0);
                tail_BFS = tail_BFS->next;
                ytail->next = new listOfObjects<int>(y1->a);
                ytail = ytail->next;
              }
            }
            y1 = y1->next;
          }
          head_BFS = head_BFS->next;
        }
        compressedmap = new listOfObjects<listOfObjects<int> *>(yhead);
        compressedmaptail = compressedmap;
      }
      else
      {
        listOfObjects<int> *yhead = new listOfObjects<int>(c);
        listOfObjects<int> *ytail = yhead;
       
        Queue_BFS *head_BFS = new Queue_BFS(c, 0);
        Queue_BFS *tail_BFS = head_BFS;
        while (head_BFS != nullptr)
        {
           similarity *y1 = head;
          while (y1 != nullptr)
          {
            if (y1->a == head_BFS->x)
            {
              if (visited[y1->b] == 0)
              {
                visited[y1->b] = 1;
                tail_BFS->next = new Queue_BFS(y1->b, 0);
                tail_BFS = tail_BFS->next;
                ytail->next = new listOfObjects<int>(y1->b);
                ytail = ytail->next;
              }
            }
            if (y1->b == head_BFS->x)
            {
              if (visited[y1->a] == 0)
              {
                visited[y1->a] = 1;
                tail_BFS->next = new Queue_BFS(y1->a, 0);
                tail_BFS = tail_BFS->next;
                ytail->next = new listOfObjects<int>(y1->a);
                ytail = ytail->next;
              }
            }
            y1 = y1->next;
          }
          head_BFS = head_BFS->next;
        }
        compressedmaptail->next = new listOfObjects<listOfObjects<int> *>(yhead);
        compressedmaptail = compressedmaptail->next;
      }
    }

    c++;
  }
  listOfObjects<listOfObjects<int> *> *printing = compressedmap;
  int numnod = 0;
  
  listOfObjects<int>* collapsedhead = nullptr;
  listOfObjects<int>* collapsedtail = nullptr;
  while (printing != nullptr)
  {
    numnod ++;
    listOfObjects<int> *garbagex = printing->object;
    int maxi = garbagex->object;
    while (garbagex != nullptr)
    {
      maxi = max(maxi,garbagex->object);
      garbagex = garbagex->next;
    }
    maxi = maxi + 1;
    if(collapsedhead == nullptr){
      collapsedhead = new listOfObjects<int>(maxi);
      collapsedtail = collapsedhead;
    }
    else{
      collapsedtail -> next = new listOfObjects<int>(maxi);
      collapsedtail = collapsedtail -> next;
    }

    // cout << endl;
    printing = printing->next;
  }
  file<<endl;
  file<<"Collapsed graph:"<<endl<<endl;
  listOfObjects<int>*xo = collapsedhead;
  file<<numnod<<": ";
  while(xo!=nullptr){
    file<<xo->object<<" ";
    xo = xo->next;
    
  }
  file<<endl;

  // for(int i =0;i<n;i++){
  //   listOfObjects<int> *myedges = graph_nodes[i].adjacenthead;
  //   while(myedges!=nullptr){

  //   }
  // }
  printing  = compressedmap;
  xo = collapsedhead;
  int mylabel[n];
  while (printing != nullptr)
  {
    
    listOfObjects<int> *garbagex = printing->object;
    
    while (garbagex != nullptr)

    {
      mylabel[garbagex->object] = xo->object;
      
      garbagex = garbagex->next;
    }
   
    
    // cout << endl;
    printing = printing->next;
    xo = xo->next;
  }
  bool final_matrix[n][n];
  for(int i =0;i<n;i++){
      final_matrix[i][i] = false;
  }
  for(int i = 0;i<n;i++){
         listOfObjects<int> *xx =  graph_nodes[i].adjacenthead;
         while(xx!=nullptr){

            if(mylabel[i] != mylabel[xx->object]){
              if(!final_matrix[mylabel[i]-1][mylabel[xx->object]-1]){
                final_matrix[mylabel[i]-1][mylabel[xx->object]-1] = true;
                file<<mylabel[i]<<" "<<mylabel[xx->object]<<endl;
            }
            }
            xx = xx->next;
         }
  }



  // for (int i = 0; i < n; i++)
  // {
  //   for (int j = 1; j < n+1; j++)
  //   {
  //     a1[i][j] = -1;
  //   }
  //   a1[i][0] = 0;
  // }

  return 0;
}
