#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::printsource()
{
  cout << "sourcecodes: ";
  for (int i = 0; i < numNodes; i++)
  {
    if (nodes[i].adjacent->from == nullptr) // parents
      cout << nodes[i].value << " ";
  }
  return;
}

bool Graph::check_similar(int num1, int num2)
{
  // if (num1 == num2) // reflexive property
  //   return true;
  bool found = false;
  listOfObjects<int> *last = nodes[num1 - 1].similar;
  while (last != nullptr)
  {
    if (last->object == num2)
    {
      found = true;
      break;
    }
    last = last->next;
  }
  return found;
}

void Graph::add_similar(int num1, int num2)
{
  if (nodes[num1 - 1].similar == nullptr)
  {
    nodes[num1 - 1].similar = new listOfObjects<int>(num2);
  }
  else
  {
    bool find = true;
    listOfObjects<int> *last = nodes[num1 - 1].similar;
    while (last != nullptr)
    {
      if (last->object == num2)
      {
        find = false;
      }
      last = last->next;
    }
    last = nodes[num1 - 1].similar;
    if (find)
    {
      while (last->next != nullptr)
      {
        last = last->next;
      }
      last->next = new listOfObjects<int>(num2);
    }
  }
  return;
}

void Graph::compute_similar()
{
  int MAT = false;
  for (int i = 0; i < numNodes; i++) // checking the third condition where n2 has only
  {
    // cout << "hi1" << endl;
    listOfObjects<int> *last = nodes[i].adjacent->from;
    int count_to = 0;
    while (last != nullptr)
    {
      // cout << "x1" << endl;
      count_to++;
      last = last->next;
    }
    if (count_to == 1)
    {
      int num2 = nodes[i].adjacent->from->object;
      // cout << "1" << nodes[i].value << " " << num2 << endl;
      add_similar(nodes[i].value, num2);
    }
    else
      continue;
  }

  for (int i = 0; i < numNodes; i++)
  {
    for (int j = 0; j < numNodes; j++)
    {
      // cout << "hi2" << endl;
      if (i != j)
      {
        bool match = true;
        int num1 = nodes[i].value;
        int num2 = nodes[j].value;
        listOfObjects<int> *last1 = nodes[i].adjacent->from; // parent to the node
        listOfObjects<int> *last2 = nullptr;
        if (last1 == nullptr)
        {
          continue;
        }
        while (last1 != nullptr)
        {
          bool m = false;
          int n1 = last1->object;
          last2 = nodes[j].adjacent->from;
          while (last2 != nullptr)
          {
            int n2 = last2->object;
            // if (i == 6 && j == 14)
            // {
            //   cout << n1 << " " << n2 << endl;
            // }
            // cout << n1 << " " << n2 << endl;
            // cout << check_similar(n1, n2) << endl;
            // cout << check_similar(n2, n1) << endl;
            if (check_similar(n1, n2))
            {
              // if (i == 6 && j == 14)
              // {
              //   cout << n1 << " " << n2 << endl;
              // }
              // cout << n1 << " " << n2 << endl;
              // cout << check_similar(n1, n2) << endl;
              // cout << check_similar(n2, n1) << endl;
              m = true;
              break;
            }
            last2 = last2->next;
          }
          if (m == false)
          {
            // cout << "faske: " << n1 << endl;
            match = false;
            break;
          }
          last1 = last1->next;
        }
        // last1 = nodes[i].adjacent->from; // parent to the node
        last2 = nodes[j].adjacent->from;
        while (last2 != nullptr)
        {
          // cout << "hello" << endl;
          bool m = false;
          int n2 = last2->object;
          last1 = nodes[i].adjacent->from;
          while (last1 != nullptr)
          {
            int n1 = last1->object;
            // cout << n1 << " " << n2 << endl;
            // cout << check_similar(n1, n2) << endl;
            // cout << check_similar(n2, n1) << endl;
            if (check_similar(n2, n1))
            {
              // cout << n1 << " " << n2 << endl;
              // cout << check_similar(n1, n2) << endl;
              // cout << check_similar(n2, n1) << endl;
              m = true;
              break;
            }
            last1 = last1->next;
          }
          if (m == false)
          {
            // cout << "faske: " << n1 << endl;
            match = false;
            break;
          }
          last2 = last2->next;
        }
        if (match == true)
        {
          // cout << num1 << " " << num2 << endl;
          add_similar(num1, num2);
        }
        // else
        //   continue;
      }
      // else
      //   continue;
    }
  }

  return;
}

void Graph::print_similar()
{
  for (int i = 0; i < numNodes; i++) // inserting the pairs that are similar into sim listing
  {
    listOfObjects<int> *last = nodes[i].similar;
    while (last != nullptr)
    {
      int num2 = last->object;
      if (sim == nullptr) // if sim is a null
      {
        sim = new listing<int>(nodes[i].value, num2);
        cout << endl;
        cout << "Similar Node pairs: (" << nodes[i].value << "," << num2 << ")";
      }
      else // if sim is not a null
      {
        listing<int> *last = sim;
        while (last->next != nullptr)
        {
          last = last->next;
        }
        last->next = new listing<int>(nodes[i].value, num2);
        cout << "(" << nodes[i].value << "," << num2 << ")";
      }
      last = last->next;
    }
  }
  cout << endl;
}

void Graph::collapse()
{
  listOfObjects<int> *list = nullptr;
  int c = 0;
  for (int i = 0; i < numNodes; i++)
  {
    // cout << "hi" << endl;
    listOfObjects<int> *last = nodes[i].similar;
    while (last != nullptr)
    {
      for (int j = 0; j < numNodes; j++)
      {
        if (maxi[j] == maxi[i])
        {
          maxi[j] = max(maxi[j], maxi[last->object - 1]);

          for (int k = 0; k < numNodes; k++)
          {
            if (maxi[k] == maxi[last->object - 1])
            {
              maxi[k] = max(maxi[k], maxi[j]);
            }
          }
          // maxi[last->object - 1] = max(maxi[j], maxi[last->object - 1]);
        }
      }
      last = last->next;
    }
  }
  // for (int i = 0; i < numNodes; i++)
  // {
  //   cout << maxi[i] << endl;
  // }
  for (int i = 0; i < numNodes; i++)
  {
    if (list == nullptr)
    {
      list = new listOfObjects<int>(maxi[i]);
      c++;
    }
    else
    {
      listOfObjects<int> *l = list;
      bool found = false;
      while (l != nullptr)
      {
        if (l->object == maxi[i])
        {
          found = true;
          break;
        }
        l = l->next;
      }
      l = list;
      while (l->next != nullptr)
      {
        l = l->next;
      }
      if (!found)
      {
        l->next = new listOfObjects<int>(maxi[i]);
        c++;
      }
    }
  }
  cout << endl;
  cout << c << ": ";
  listOfObjects<int> *l = list;
  while (list != nullptr)
  {
    cout << list->object << " ";
    list = list->next;
  }
  cout << endl;
}
#endif
