void matrixRotation(vector<vector<int>> matrix, int r)
{
    int size, sizerow;
    if (matrix.size() >= 2 && matrix.size() <= 300 && matrix[0].size() >= 2 && matrix[0].size() <= 300)
    {
        size = matrix.size();
        sizerow = matrix[0].size();
    }
    int halfSize = size / 2;
    int halfSizer = sizerow / 2;
    
    // create new 2d arrays and poiners
    vector<vector<int*>> one(size, vector<int*>(sizerow));
    vector<vector<int*>> two(size, vector<int*>(sizerow));
    vector<vector<int*>>* even = &one;
    vector<vector<int*>>* odd = &two;

    for (int a = 0; a < size; ++a)
    {
        for (int b = 0; b < sizerow; ++b)
        {
            two[a][b] = one[a][b] = &(matrix[a][b]);            
        }
    }

 // main loop >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    if (r > 1)
    {
        // create count of layers of matrix and array of sum of steps for each layer for skip no need steps
        int countOfLayer = 0;
        if (size % 2 != 1 && sizerow % 2 != 1)
        {
            if (size > sizerow)
            {
                countOfLayer = halfSizer;
            }
            else
            {
                countOfLayer = halfSize;
            }
        }
        else if (size % 2 != 1)
        {
            countOfLayer = halfSize;
        }
        else
        {
            countOfLayer = halfSizer;
        }

        vector<int> steps(countOfLayer);
        int front = (size + sizerow + size + sizerow) - 4;
        for (int i = 0; i < countOfLayer; ++i)
        {
            if (r <= front)
            {
                steps[i] = r;
                front -= 8;
            }
            else
            {
                steps[i] = (r % front);
                front -= 8;
            }
        }
        // >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

        int currentLayer = (size + sizerow + size + sizerow) - 4;
        for (int loop = 0; loop < countOfLayer; ++loop)
        {
            vector<int*> orderOfLayersNum(currentLayer);
            int left = 1;
            int right = 0;
            int top = 0;
            int bottom = sizerow + size + sizerow - 3 - (loop * 6);
            for (int a = loop; a < size - loop; ++a)
            {
                for (int b = loop; b < sizerow - loop; ++b)
                {
                    if (b != loop && a != loop && a + 1 + loop != size && b + 1 + loop != sizerow) continue;
                    // <<<<<<< top <<<<<<<<
                    if (a == loop)
                    {
                        orderOfLayersNum[top] = one[a][b];
                        ++top;
                        continue;
                    }
                    // >>>>>>> bottom >>>>>>>
                    if (a + 1 + loop == size)
                    {
                        orderOfLayersNum[bottom] = one[a][b];
                        --bottom;
                        continue;
                    }
                    // left col
                    if (b == loop && a != loop && a + 1 + loop != size)
                    {
                        orderOfLayersNum[currentLayer - left] = one[a][b];
                        ++left;
                        continue;
                    }
                    // right col
                    if (b + 1 + loop == sizerow && a != loop && a + 1 + loop != size)
                    {
                        orderOfLayersNum[top + right] = one[a][b];
                        ++right;
                        continue;
                    }
                }
            }
            // reset >>>>>>> 
            left = 1;
            right = 0;
            top = 0;
            bottom = sizerow + size + sizerow - 3 - (loop * 6);
            int change = 0;

            for (int a = loop; a < size - loop; ++a)
            {
                for (int b = loop; b < sizerow - loop; ++b)
                {
                    if (b != loop && a != loop && a + 1 + loop != size && b + 1 + loop != sizerow) continue;
                    // <<<<<<< top <<<<<<<<
                    if (a == loop)
                    {
                        if (top + steps[loop] >= currentLayer)
                        {
                            change = top + steps[loop] - currentLayer;
                            one[a][b] = orderOfLayersNum[change];
                        }
                        else
                        {
                            one[a][b] = orderOfLayersNum[top + steps[loop]];
                        }
                        ++top;
                        continue;
                    }
                    // >>>>>>> bottom >>>>>>>
                    if (a + 1 + loop == size)
                    {
                        if (bottom + steps[loop] >= currentLayer)
                        {
                            change = bottom + steps[loop] - currentLayer;
                            one[a][b] = orderOfLayersNum[change];
                        }
                        else
                        {
                            one[a][b] = orderOfLayersNum[bottom + steps[loop]];
                        }
                        --bottom;
                        continue;
                    }
                    // left col
                    if (b == loop && a != loop && a + 1 + loop != size)
                    {
                        if (currentLayer - left + steps[loop] >= currentLayer)
                        {
                            change = currentLayer - left + steps[loop] - currentLayer;
                            one[a][b] = orderOfLayersNum[change];
                        }
                        else
                        {
                            one[a][b] = orderOfLayersNum[currentLayer - left + steps[loop]];
                        }
                        ++left;
                        continue;
                    }
                    // right col
                    if (b + 1 + loop == sizerow && a != loop && a + 1 + loop != size)
                    {
                        if (top + right + steps[loop] >= currentLayer)
                        {
                            change = top + right + steps[loop] - currentLayer;
                            one[a][b] = orderOfLayersNum[change];
                        }
                        else
                        {
                            one[a][b] = orderOfLayersNum[top + right + steps[loop]];
                        }
                        ++right;
                        continue;
                    }
                }
            }            
            currentLayer -= 8;
        }
    }
    else
    {
        bool exit = true;
        int rotation = 0;
        while (exit)
        {
            for (int loop = 0; loop <= halfSize || loop <= halfSizer; ++loop)
            {
                for (int a = 0 + loop; a < size - loop; ++a)
                {
                    for (int b = 0 + loop; b < sizerow - loop; ++b)
                    {
                        if (b != loop && a != loop && a + 1 + loop != size && b + 1 + loop != sizerow) continue;
                        // down left col
                        if (b == loop && a + 1 + loop != size)
                        {
                            (*odd)[a + 1][b] = (*even)[a][b];
                            continue;
                        }
                        // <<<<<<< top <<<<<<<<
                        if (b > a && a == loop)
                        {
                            (*odd)[a][b - 1] = (*even)[a][b];
                            continue;
                        }
                        // >>>>>>> bottom >>>>>>>
                        if (a + 1 + loop == size && b + 1 + loop < sizerow)
                        {
                            (*odd)[a][b + 1] = (*even)[a][b];
                            continue;
                        }
                        // top right col
                        if (b + 1 + loop == sizerow && a > loop)
                        {
                            (*odd)[a - 1][b] = (*even)[a][b];
                            continue;
                        }
                        //for center ( if is it)
                        if (size % 2 && a == halfSize && sizerow % 2 && b == halfSizer)
                        {
                            (*odd)[a][b] = &*(*even)[a][b];
                        }
                    }
                }
            }
            ++rotation;

            if (rotation == 1 || rotation % 2 == 1)
            {
                odd = &one;
                even = &two;
            }
            else
            {
                even = &one;
                odd = &two;
            }
            // exit >>>>>>>>>>>>>>>>>>>>>
            if (rotation == r)
            {
                exit = false;
            }
        }
    }
 // end of main loop and print result >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
    for (int a = 0; a < size; ++a)
    {
        for (int b = 0; b < sizerow; ++b)
        {
            if (b < sizerow - 1)
            {
                cout << *(*even)[a][b] << ' ';
            }
            else
            {
                cout << *(*even)[a][b] << '\n';
            }
        }
    }
}
