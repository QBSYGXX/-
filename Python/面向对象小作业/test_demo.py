
from abc import ABC,abstractmethod
from typing import List,Dict,Optional
import weakref#弱引用模块，用于处理可能的内存泄漏
#抽象基类
class Employee(ABC):
    _instances=[]#跟踪所有实例（演示，实际项目可能不需要）
    def __init__(self,employee_id:int,name:str,position:str,salary:float):
        self.employee_id=employee_id
        self.name=name
        self.position=position
        self.salary=salary
    @abstractmethod
    def calculate_bonus(self)->float:
           """计算奖金 - 抽象方法，子类必须实现"""
           pass
    def get_info(self)->str:
        """获取职工信息"""
        return f"ID: {self.employee_id}, Name: {self.name}, Position: {self.position}, Salary: {self.salary}"
    def __str__(self)->str:
        return self.get_info()
    def __del__(self):
        print(f"职工ID：{self.employee_id}，姓名：{self.name}被销毁")
        """从实例列表中移除（如果有）"""
        for i,ref in enumerate(Employee._instances):
            if ref() is self:
                del Employee._instances[i]
                break

    @classmethod
    def get_active_instances(cls):
        """获取收益所有活跃的实例（仅用于演示）"""
        return [ref() for ref in cls._instances if ref() is not None]


#普通员工类
class RegularEmployee(Employee):
    def __init__(self,employee_id:int,name:str,salary:float,department:str):
        super().__init__(employee_id,name,"普通员工",salary)
        self.department=department
    def calculate_bonus(self)->float:#重写函数
        """普通员工的奖金是薪资的10%"""
        return self.salary * 0.10
    def get_info(self)->str:
        base_info=super().get_info()
        return f"{base_info}，部门：{self.department}，奖金：{self.calculate_bonus():.2f}，薪资：{self.salary:.2f}"
#高管类
class Executive(Employee):
    def __init__(self,employee_id:int,name:str,salary:float,stock_options:float):
        super().__init__(employee_id,name,"高管",salary)
        self.stock_options =stock_options
    def calculate_bonus(self)->float:
        # 高管的奖金是薪资的25%加上股票期权价值
        return self.salary * 0.25+self.stock_options*10
    def get_info(self)->str:
        base_info=super().get_info()
        return f"{base_info},股票期权：{self.stock_options:.2f}，奖金：{self.calculate_bonus():.2f}"
#老板类
class Boss(Employee):
    def __init__(self,employee_id:int,name:str,salary:float,company_share:float):
        super().__init__(employee_id,name,"老板",salary)
        self.company_share=company_share
    def calculate_bonus(self)->float:
        company_profit=10000
        return self.company_share*company_profit+self.salary*0.5
    def get_info(self)->str:
        base_info=super().get_info()
        return f"{base_info}，公司股份：{self.company_share*100:.2f}%，奖金：{self.calculate_bonus():.2f}"
#使用上下文管理器管理资源
class EmployeeManagerSystem:
    def __init__(self):
        self.employees:Dict[int,Employee]={}
        self.next_id=1
        print("职工管理系统被创建")
    def __enter__(self):
        # 管理上下文入口
        return self
    def __exit__(self,exc_type,exc_val,exc_tb):
        """上下文管理器出口，用于清理资源"""
        print("清理职工管理系统资源...")
        self.employees.clear()
        print("职工管理系统已清理")
    def add_employee(self,employee:Employee):
        self.employees[employee.employee_id]=employee
        print(f"成功添加职工：{employee.name}")
    def remove_employee(self,employee_id:int)->bool:
        if employee_id in self.employees:
            employee=self.employees.pop(employee_id)
            print(f"成功删除职工：{employee.name}")
            return True
        else:
            print(f"未找到ID为{employee_id}的职工")
            return False
    def find_employee(self,employee_id:int)->Optional[Employee]:
        return self.employees.get(employee_id)
    def update_employee(self,employee_id:int,**kwargs)->bool:
        if employee_id not in self.employees:
            print(f"未找到ID为{employee_id}的职工")
            return False
        employee=self.employees[employee_id]
        for key,value in kwargs.items():
            if hasattr(employee,key):
                setattr(employee,key,value)
            else:
                print(f"无效属性：{key}")
        print(f"成功更新职工{employee.name}的信息")
        return True
    def list_employees(self)->None:
        if not self.employees:
            print("系统暂无职工")
            return
        print("\n===职工列表===")
        for employee in self.employees.values():
            print(employee)
            print("=============")
    def increment_id(self)->None:
        self.next_id += 1
    def get_next_id(self)->int:
        return self.next_id
    def __del__(self):
        print("职工管理系统被销毁")
#演示内存管理和析构函数
def demo_memory_management():
    print("===内存管理展示===")
    with EmployeeManagerSystem() as system:
        #添加一些职工
        emp1 =RegularEmployee(system.get_next_id(),"李四",5000,"技术部")
        system.add_employee(emp1)
        system.increment_id()
        #列出所有职工
        system.list_employees()
        #删除一个职工
        system.remove_employee(1)
        #查看活跃案例
        print(f"\n活跃度职工示例：{len(Employee.get_active_instances())}")
    #上下文管理器退出后，资源会自动清理
    print("演示结束")
def main():
    demo_memory_management()
    #强制进行垃圾回收
    import gc
    gc.collect()
    print("\n程序结束")
if __name__ == "__main__":
    main()
