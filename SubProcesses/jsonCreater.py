import json
import datetime
import os
import numpy as np
import parameters as p


class NumpyEncoder(json.JSONEncoder):
    """ Special json encoder for numpy types """

    def default(self, obj):
        if isinstance(obj, (np.int_, np.intc, np.intp, np.int8,
                            np.int16, np.int32, np.int64, np.uint8,
                            np.uint16, np.uint32, np.uint64)):
            return int(obj)
        elif isinstance(obj, (np.float_, np.float16, np.float32,
                              np.float64)):
            return float(obj)
        elif isinstance(obj, (np.ndarray,)):
            return obj.tolist()
        return json.JSONEncoder.default(self, obj)

sep = os.path.sep
path = "Files" + sep


def createJson(dict):
    JsonFile = json.dumps(dict, indent=4)
    return JsonFile


def saveJson(dict):
    fileName = path + datetime.datetime.now().strftime(p.dateformatting) + ".json"
    with open(fileName, 'w') as f:
        json.dump(dict, f, indent=4, cls=NumpyEncoder)
    f.close()
