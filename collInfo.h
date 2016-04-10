class CollInfoC
{
public:
    typedef enum 
    {
        SHAPE_INVALID,
        SHAPE_CIRCLE,
        SHAPE_RECTANGLE,
        SHAPE_MAX
    }CollisionShapes;
    
    CollisionShapes shape;
    float_t param1;
    float_t param2;
};