class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        for(int i = 0; i < stones.size(); i++)
        {
            for(int j = 0; j < stones.size(); j++)
            {
                if(stones[i] < stones[j])
                {
                    int temp = stones[j];
                    stones[j] = stones[i];
                    stones[i] = temp;
                }
            }
        }

        while(true)
        {
            if(stones.size() <= 1)
            {
                break;
            }

            int size = stones.size();
            int heavier_stone = stones[size - 1];
            int heavy_stone = stones[size - 2];

            if(heavier_stone == heavy_stone)
            {
                stones.pop_back();
                stones.pop_back();
            }
            else
            {
                int residual = heavier_stone - heavy_stone;
                stones.pop_back();
                stones.pop_back();

                int current_index = -1;
                for(int i = 0; i < stones.size(); i++)
                {
                    current_index = i;
                    if(stones[i] >= residual)
                    {
                        break;
                    }
                }

                if(current_index != -1)
                {
                    if(stones[current_index] == residual)
                    {
                        stones.insert(stones.begin() + current_index, residual);
                    }
                    else if(stones[current_index] > residual)
                    {
                        stones.insert(stones.begin() + current_index, residual);
                    }
                    else
                    {
                        stones.push_back(residual);
                    }
                }
                else
                {
                    stones.push_back(residual);
                }
            }
        }

        return stones.size() == 1 ? stones[0] : 0;
    }
};