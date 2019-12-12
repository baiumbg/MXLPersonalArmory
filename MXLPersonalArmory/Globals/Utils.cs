using System;
using System.Collections.Generic;
using System.Linq;

namespace MXLPersonalArmory.Globals
{
    class Utils<T>
    {
        public static string ListToString(List<T> list)
        {
            string listAsString = String.Concat(list.Select(o => o.ToString() + ", "));
            if (listAsString.Length > 0)
            {
                listAsString = listAsString.Remove(listAsString.Length - 3);
            }
            return listAsString;
        }
    }
}
