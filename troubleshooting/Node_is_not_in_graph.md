# Node is not in graph

## 적용코드

- 모듈 설정

```python
import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt
%matplotlib inline
from keras import backend as K #이건 뭐하는 모듈?
```

- 케라스를 통해 모델 생성 및 save

```python
X = np.array([[0,0], [0,1], [1,0], [1,1]], 'float32')
Y = np.array([[0], [1], [1], [0]], 'float32')

model = tf.keras.models.Sequential()
model.add(tf.keras.layers.Dense(64, input_dim=2, activation='relu'))
model.add(tf.keras.layers.Dense(64, activation='relu'))

model.add(tf.keras.layers.Dense(64, activation='relu'))
model.add(tf.keras.layers.Dense(64, activation='relu'))
model.add(tf.keras.layers.Dense(1, activation ='sigmoid', name='Output'))


model.compile(loss='mean_squared_error', optimizer='adam', metrics=['binary_accuracy'])

model.fit(X, Y, batch_size=1, epochs=100, verbose=0)


model.summary()

#input/output.op.name 텐서플로우가 가지고 있는 실제 name을 호출

# inputs: 
print('inputs: ', [input.op.name for input in model.inputs])

# outputs: 
print('outputs: ', [output.op.name for output in model.outputs]) 

#model save
model.save('xor.h5')

"""Out result
Model: "sequential"
_________________________________________________________________
Layer (type)                 Output Shape              Param #   
=================================================================
dense (Dense)                (None, 64)                192       
_________________________________________________________________
dense_1 (Dense)              (None, 64)                4160      
_________________________________________________________________
dense_2 (Dense)              (None, 64)                4160      
_________________________________________________________________
dense_3 (Dense)              (None, 64)                4160      
_________________________________________________________________
Output (Dense)               (None, 1)                 65        
=================================================================
Total params: 12,737
Trainable params: 12,737
Non-trainable params: 0
_________________________________________________________________
inputs:  ['dense_input']
outputs:  ['Output/Identity']

"""
```

- freeze_session 함수를 통해 케라스 모델을 `.pb` 또는 `.pbtxt`  형식으로 저장하는 코드

```python
from tensorflow.compat.v1.keras import backend as K
import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()


def freeze_session(session, keep_var_names=None, output_names=None, clear_devices=True):
    """
    Freezes the state of a session into a pruned computation graph.

    Creates a new computation graph where variable nodes are replaced by
    constants taking their current value in the session. The new graph will be
    pruned so subgraphs that are not necessary to compute the requested
    outputs are removed.
    @param session The TensorFlow session to be frozen.
    @param keep_var_names A list of variable names that should not be frozen,
                          or None to freeze all the variables in the graph.
    @param output_names Names of the relevant graph outputs.
    @param clear_devices Remove the device directives from the graph for better portability.
    @return The frozen graph definition.
    """
    graph = session.graph
    with graph.as_default():
        freeze_var_names = list(set(v.op.name for v in tf.global_variables()).difference(keep_var_names or []))
        output_names = output_names or []
        output_names += [v.op.name for v in tf.global_variables()]
        input_graph_def = graph.as_graph_def()
        if clear_devices:
            for node in input_graph_def.node:
                node.device = ''
        frozen_graph = tf.graph_util.convert_variables_to_constants(
            session, input_graph_def, output_names, freeze_var_names)
        return frozen_graph


#K.get_session() 열려있는 세션을 가져옴
frozen_graph = freeze_session(K.get_session(), output_names=[out.op.name for out in model.outputs]) #'output/Sigmoid'
tf.train.write_graph(frozen_graph, './', 'xor.pbtxt', as_text=True) #txt로 저장
tf.train.write_graph(frozen_graph, './', 'xor.pb', as_text=False) #바이너리로 저장
```





## 에러 증상

- Freeze_session을 통해 케라스 모델을  `.pb` 또는 `.pbtxt`  형식으로 저장할 때 `AssertionError` 발생

```python
---------------------------------------------------------------------------
AssertionError                            Traceback (most recent call last)
<ipython-input-4-9026d45a39c8> in <module>
     34 
     35 #K.get_session() 열려있는 세션을 가져옴
---> 36 frozen_graph = freeze_session(K.get_session(), output_names=[out.op.name for out in model.outputs]) #'output/Sigmoid'
     37 tf.train.write_graph(frozen_graph, './', 'xor.pbtxt', as_text=True) #txt로 저장
     38 tf.train.write_graph(frozen_graph, './', 'xor.pb', as_text=False) #바이너리로 저장

<ipython-input-4-9026d45a39c8> in freeze_session(session, keep_var_names, output_names, clear_devices)
     29                 node.device = ''
     30         frozen_graph = tf.graph_util.convert_variables_to_constants(
---> 31             session, input_graph_def, output_names, freeze_var_names)
     32         return frozen_graph
     33 

~\.conda\envs\myoung_lab\lib\site-packages\tensorflow_core\python\util\deprecation.py in new_func(*args, **kwargs)
    322               'in a future version' if date is None else ('after %s' % date),
    323               instructions)
--> 324       return func(*args, **kwargs)
    325     return tf_decorator.make_decorator(
    326         func, new_func, 'deprecated',

~\.conda\envs\myoung_lab\lib\site-packages\tensorflow_core\python\framework\graph_util_impl.py in convert_variables_to_constants(sess, input_graph_def, output_node_names, variable_names_whitelist, variable_names_blacklist)
    275   # This graph only includes the nodes needed to evaluate the output nodes, and
    276   # removes unneeded nodes like those involved in saving and assignment.
--> 277   inference_graph = extract_sub_graph(input_graph_def, output_node_names)
    278 
    279   # Identify the ops in the graph.

~\.conda\envs\myoung_lab\lib\site-packages\tensorflow_core\python\util\deprecation.py in new_func(*args, **kwargs)
    322               'in a future version' if date is None else ('after %s' % date),
    323               instructions)
--> 324       return func(*args, **kwargs)
    325     return tf_decorator.make_decorator(
    326         func, new_func, 'deprecated',

~\.conda\envs\myoung_lab\lib\site-packages\tensorflow_core\python\framework\graph_util_impl.py in extract_sub_graph(graph_def, dest_nodes)
    195   name_to_input_name, name_to_node, name_to_seq_num = _extract_graph_summary(
    196       graph_def)
--> 197   _assert_nodes_are_present(name_to_node, dest_nodes)
    198 
    199   nodes_to_keep = _bfs_for_reachable_nodes(dest_nodes, name_to_input_name)

~\.conda\envs\myoung_lab\lib\site-packages\tensorflow_core\python\framework\graph_util_impl.py in _assert_nodes_are_present(name_to_node, nodes)
    150   """Assert that nodes are present in the graph."""
    151   for d in nodes:
--> 152     assert d in name_to_node, "%s is not in graph" % d
    153 
    154 

AssertionError: output/Identity is not in graph

```



## 발생원인

- 텐서플로우 2.x 버전에서 모델 생성 후 Output name 호출 시 output이 graph 에 없다고 에러 발생, 버전에 따른 설정이 바뀐것 같다.
  - `AssertionError: Node is not in graph`

- 유사에러
  - https://github.com/tensorflow/tensorflow/issues/3986



## 해결방법

1. 텐서플로 버전을 하위버전으로 사용하여 모델 output name에 `Identify -> Activation func으로 변경 되었는지 컴파일 하면서 확인 후 재컴파일` 

2. 모듈을 애초에 하위버전으로 낮추고 컴파일 진행하면 괜찮다.

   ```python
   from tensorflow.compat.v1.keras import backend as K
   import tensorflow.compat.v1 as tf
   tf.disable_v2_behavior()
   ```

   