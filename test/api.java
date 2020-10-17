import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Iterator;
import java.util.List;

import org.objectweb.asm.ClassReader;
import org.objectweb.asm.ClassWriter;
import org.objectweb.asm.tree.AbstractInsnNode;
import org.objectweb.asm.tree.ClassNode;
import org.objectweb.asm.tree.FieldInsnNode;
import org.objectweb.asm.tree.InsnList;
import org.objectweb.asm.tree.LdcInsnNode;
import org.objectweb.asm.tree.MethodInsnNode;
import org.objectweb.asm.tree.MethodNode;
import static org.objectweb.asm.Opcodes.*;
public class api {

	public static void main(String[] args) throws Exception {

		//read in, build classNode
		ClassNode classNode=new ClassNode();
		ClassReader cr=new ClassReader("Test.java");
		cr.accept(classNode, 0);

		//peek at classNode and modifier
		List<MethodNode> methods=(List<MethodNode>)classNode.methods;
		for(MethodNode method: methods) {
			System.out.println("name="+method.name+" desc="+method.desc);
			InsnList insnList=method.instructions;
			Iterator ite=insnList.iterator();
			while(ite.hasNext()) {
				AbstractInsnNode insn=(AbstractInsnNode)ite.next();
				int opcode=insn.getOpcode();
				//add before return: System.out.println("Returning ... ")
				
			}
		}
		

	}

}

