// 13-priority_queue.cpp
// 实现个人待办事项--std::priority_queue

#include <iostream>
#include <queue>
#include <tuple>
#include <string>

int main(){
    using item_type = std::pair<int, std::string>;      // 将待办事项和优先级队列存在一起
    std::priority_queue<item_type> q;       // 实例化一个优先级队列    
    std::initializer_list<item_type> il{
        {1, "dishes"},
        {0, "watch tv"},
        {2, "do homework"},
        {0, "read comics"},
    };
    for(const auto &p : il){
        q.push(p);      // 将元素推入队列中
    }
    while(!q.empty()){  // 浏览列表中优先级最高的事件
        std::cout << q.top().first << ": " << q.top().second << std::endl;
        q.pop();        // 移除队首元素
    }
    std::cout << std::endl;
}